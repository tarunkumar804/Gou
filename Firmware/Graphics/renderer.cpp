#include <vector>
#include <cstdint>
#include <stdexcept>
#include <chrono>
#include <string>
#include <fstream>
#include <algorithm>

namespace graphics_primitive {

class Renderer {
private:
    std::vector<uint8_t> frame_buffer;
    bool is_initialized = false;
    std::chrono::duration<double> last_render_time = std::chrono::duration<double>::zero();

    // Display properties
    struct DisplayConfig {
        int64_t width;
        int64_t height;
        uint32_t bytes_per_pixel = 4; // Default RGBA
    } display_config;

public:
    // Color struct for cleaner parameter passing
    struct Color {
        uint8_t r, g, b, a;
        Color(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t a_ = 255) 
            : r(r_), g(g_), b(b_), a(a_) {}
    };

    // Constructor with default values
    Renderer(int64_t width = 1920, int64_t height = 1080) {
        initialize(width, height);
    }

    // Initialize or resize display
    void initialize(int64_t width, int64_t height) {
        if (width <= 0 || height <= 0) {
            throw std::invalid_argument("Display dimensions must be positive");
        }
        
        display_config.width = width;
        display_config.height = height;
        frame_buffer.resize(width * height * display_config.bytes_per_pixel);
        is_initialized = true;
    }

    // Send frame buffer to display with timing
    bool send_to_display(uint64_t display_port_address) {
        if (!is_initialized) {
            throw std::runtime_error("Renderer not initialized");
        }
        
        try {
            volatile uint8_t* port = reinterpret_cast<volatile uint8_t*>(display_port_address);
            size_t buffer_size = frame_buffer.size();
            
            auto start = std::chrono::high_resolution_clock::now();
            for (size_t i = 0; i < buffer_size; i++) {
                port[i] = frame_buffer[i];
            }
            auto end = std::chrono::high_resolution_clock::now();
            last_render_time = end - start;
            
            return true;
        }
        catch (const std::exception& e) {
            return false;
        }
    }

    // Clear screen with specific color
    void clear(Color color = Color(0, 0, 0, 255)) {
        if (!is_initialized) return;
        
        for (size_t i = 0; i < frame_buffer.size(); i += display_config.bytes_per_pixel) {
            frame_buffer[i] = color.r;
            frame_buffer[i + 1] = color.g;
            frame_buffer[i + 2] = color.b;
            frame_buffer[i + 3] = color.a;
        }
    }

    // Draw pixel at coordinates
    void draw_pixel(int64_t x, int64_t y, Color color) {
        if (!is_initialized || x < 0 || y < 0 || 
            x >= display_config.width || y >= display_config.height) {
            return;
        }
        
        size_t index = (y * display_config.width + x) * display_config.bytes_per_pixel;
        frame_buffer[index] = color.r;
        frame_buffer[index + 1] = color.g;
        frame_buffer[index + 2] = color.b;
        frame_buffer[index + 3] = color.a;
    }

    // Draw line using Bresenham's algorithm
    void draw_line(int64_t x0, int64_t y0, int64_t x1, int64_t y1, Color color) {
        int64_t dx = std::abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
        int64_t dy = -std::abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
        int64_t err = dx + dy;

        while (true) {
            draw_pixel(x0, y0, color);
            if (x0 == x1 && y0 == y1) break;
            int64_t e2 = 2 * err;
            if (e2 >= dy) { err += dy; x0 += sx; }
            if (e2 <= dx) { err += dx; y0 += sy; }
        }
    }

    // Draw rectangle outline
    void draw_rectangle(int64_t x, int64_t y, int64_t width, int64_t height, Color color) {
        if (!is_initialized || width <= 0 || height <= 0) return;
        
        int64_t x2 = x + width - 1;
        int64_t y2 = y + height - 1;
        draw_line(x, y, x2, y, color);      // Top
        draw_line(x2, y, x2, y2, color);    // Right
        draw_line(x2, y2, x, y2, color);    // Bottom
        draw_line(x, y2, x, y, color);      // Left
    }

    // Draw filled rectangle
    void fill_rectangle(int64_t x, int64_t y, int64_t width, int64_t height, Color color) {
        if (!is_initialized || width <= 0 || height <= 0) return;
        
        int64_t x1 = std::max<int64_t>(0, x);
        int64_t y1 = std::max<int64_t>(0, y);
        int64_t x2 = std::min<int64_t>(display_config.width, x + width);
        int64_t y2 = std::min<int64_t>(display_config.height, y + height);

        for (int64_t py = y1; py < y2; ++py) {
            for (int64_t px = x1; px < x2; ++px) {
                size_t index = (py * display_config.width + px) * display_config.bytes_per_pixel;
                frame_buffer[index] = color.r;
                frame_buffer[index + 1] = color.g;
                frame_buffer[index + 2] = color.b;
                frame_buffer[index + 3] = color.a;
            }
        }
    }

    // Copy a region of the frame buffer
    void copy_region(int64_t src_x, int64_t src_y, int64_t width, int64_t height, 
                     int64_t dst_x, int64_t dst_y) {
        if (!is_initialized || width <= 0 || height <= 0) return;

        for (int64_t dy = 0; dy < height; ++dy) {
            int64_t sy = src_y + dy;
            int64_t dy_pos = dst_y + dy;
            if (sy < 0 || sy >= display_config.height || 
                dy_pos < 0 || dy_pos >= display_config.height) continue;

            for (int64_t dx = 0; dx < width; ++dx) {
                int64_t sx = src_x + dx;
                int64_t dx_pos = dst_x + dx;
                if (sx < 0 || sx >= display_config.width || 
                    dx_pos < 0 || dx_pos >= display_config.width) continue;

                size_t src_index = (sy * display_config.width + sx) * display_config.bytes_per_pixel;
                size_t dst_index = (dy_pos * display_config.width + dx_pos) * display_config.bytes_per_pixel;
                for (uint32_t b = 0; b < display_config.bytes_per_pixel; ++b) {
                    frame_buffer[dst_index + b] = frame_buffer[src_index + b];
                }
            }
        }
    }

    // Save frame buffer to PPM file
    bool save_to_file(const std::string& filename) {
        if (!is_initialized) return false;

        std::ofstream file(filename, std::ios::binary);
        if (!file) return false;

        file << "P6\n" << display_config.width << " " << display_config.height << "\n255\n";
        for (size_t i = 0; i < frame_buffer.size(); i += display_config.bytes_per_pixel) {
            file.put(frame_buffer[i]);     // R
            file.put(frame_buffer[i + 1]); // G
            file.put(frame_buffer[i + 2]); // B
            // Skip alpha channel for PPM
        }
        return true;
    }

    // Getters
    int64_t get_width() const { return display_config.width; }
    int64_t get_height() const { return display_config.height; }
    size_t get_buffer_size() const { return frame_buffer.size(); }
    uint8_t* get_frame_buffer() { return frame_buffer.data(); }
    std::chrono::duration<double> get_last_render_time() const { return last_render_time; }
};

} // namespace graphics_primitive

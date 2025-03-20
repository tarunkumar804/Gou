#include <vector>
#include <cstdint>
#include <stdexcept>
#include <memory>
#include <chrono>
#include <string>

class Renderer {
private:
    std::vector<uint8_t> frame_buffer;
    uint64_t last_display_port = 0;
    bool is_initialized = false;
    
    // Display properties
    struct DisplayConfig {
        int64_t width;
        int64_t height;
        uint32_t bytes_per_pixel = 4; // Default RGBA
    } display_config;

public:
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

    // Send frame buffer to display with error checking
    bool send_to_display(uint64_t display_port_address) {
        if (!is_initialized) {
            throw std::runtime_error("Renderer not initialized");
        }
        
        try {
            volatile uint8_t* port = reinterpret_cast<volatile uint8_t*>(display_port_address);
            size_t buffer_size = frame_buffer.size();
            
            // Measure rendering time
            auto start = std::chrono::high_resolution_clock::now();
            
            for (size_t i = 0; i < buffer_size; i++) {
                port[i] = frame_buffer[i];
            }
            
            auto end = std::chrono::high_resolution_clock::now();
            last_display_port = display_port_address;
            
            return true;
        }
        catch (const std::exception& e) {
            return false;
        }
    }

    // Clear screen with specific color
    void clear(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 255) {
        if (!is_initialized) return;
        
        for (size_t i = 0; i < frame_buffer.size(); i += display_config.bytes_per_pixel) {
            frame_buffer[i] = r;     // Red
            frame_buffer[i + 1] = g; // Green
            frame_buffer[i + 2] = b; // Blue
            frame_buffer[i + 3] = a; // Alpha
        }
    }

    // Draw pixel at coordinates
    void draw_pixel(int64_t x, int64_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
        if (!is_initialized || x < 0 || y < 0 || 
            x >= display_config.width || y >= display_config.height) {
            return;
        }
        
        size_t index = (y * display_config.width + x) * display_config.bytes_per_pixel;
        frame_buffer[index] = r;
        frame_buffer[index + 1] = g;
        frame_buffer[index + 2] = b;
        frame_buffer[index + 3] = a;
    }

    // Draw line using Bresenham's algorithm
    void draw_line(int64_t x0, int64_t y0, int64_t x1, int64_t y1,
                  uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
        int64_t dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
        int64_t dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
        int64_t err = dx + dy;

        while (true) {
            draw_pixel(x0, y0, r, g, b, a);
            if (x0 == x1 && y0 == y1) break;
            int64_t e2 = 2 * err;
            if (e2 >= dy) { err += dy; x0 += sx; }
            if (e2 <= dx) { err += dx; y0 += sy; }
        }
    }

    // Get display dimensions
    int64_t get_width() const { return display_config.width; }
    int64_t get_height() const { return display_config.height; }
    
    // Get frame buffer size in bytes
    size_t get_buffer_size() const { return frame_buffer.size(); }
    
    // Get pointer to raw frame buffer
    uint8_t* get_frame_buffer() { return frame_buffer.data(); }
    
    // Save frame buffer to file (for debugging)
    bool save_to_file(const std::string& filename) {
        // Implementation would depend on file format requirements
        // This is a placeholder
        return false;
    }
};

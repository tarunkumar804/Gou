#include <vector>
#include <cstdint>
#include <stdexcept>
#include <memory>
#include <chrono>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cmath>
#include <array>
#include <utility>
#include <numeric>
#include <functional>

namespace graphics_primitive {

enum class PixelFormat {
    RGBA8888, // 4 bytes per pixel (Red, Green, Blue, Alpha)
    RGB565,   // 2 bytes per pixel (5 bits Red, 6 bits Green, 5 bits Blue)
    ARGB8888, // 4 bytes per pixel (Alpha, Red, Green, Blue)
    GRAY8     // 1 byte per pixel (Grayscale)
};

enum class BlendMode {
    NORMAL,
    ADDITIVE,
    MULTIPLY,
    SUBTRACTIVE
};

// Simple font structure for variable sizes
struct Font {
    int size; // Font size in pixels (e.g., 8 for 8x8 font)
    std::map<char, std::vector<uint8_t>> bitmap_data;
    Font(int s = 8) : size(s) {}
};

class Renderer {
private:
    std::vector<uint8_t> front_buffer; // Displayed buffer
    std::vector<uint8_t> back_buffer;  // Drawing buffer
    uint64_t last_display_port = 0;
    bool is_initialized = false;
    BlendMode current_blend_mode = BlendMode::NORMAL;

    struct DisplayConfig {
        int64_t width;
        int64_t height;
        PixelFormat format = PixelFormat::RGBA8888;
        uint32_t bytes_per_pixel = 4;
    } display_config;

    struct ClipRect {
        int64_t x, y, w, h;
        ClipRect() : x(0), y(0), w(0), h(0) {}
    } clip_rect;

    static std::map<char, std::vector<uint8_t>> default_font_data;

    // Helper to check if a point is within the clipping region
    bool is_in_clip(int64_t x, int64_t y) const {
        return x >= clip_rect.x && x < clip_rect.x + clip_rect.w &&
               y >= clip_rect.y && y < clip_rect.y + clip_rect.h;
    }

    // Helper functions for anti-aliased drawing
    static int64_t ipart(float x) { return static_cast<int64_t>(std::floor(x)); }
    static float fpart(float x) { return x - std::floor(x); }
    static int64_t round(float x) { return static_cast<int64_t>(std::round(x)); }

    // Optimized horizontal line drawing
    void draw_hline(int64_t x1, int64_t x2, int64_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        if (!is_initialized || y < clip_rect.y || y >= clip_rect.y + clip_rect.h) return;
        int64_t start = std::max(x1, clip_rect.x);
        int64_t end = std::min(x2, clip_rect.x + clip_rect.w - 1);
        if (start > end) return;

        size_t index = (y * display_config.width + start) * display_config.bytes_per_pixel;
        switch (display_config.format) {
            case PixelFormat::RGBA8888:
                for (int64_t x = start; x <= end; x++) {
                    blend_pixel(x, y, r, g, b, a);
                }
                break;
            case PixelFormat::ARGB8888:
                for (int64_t x = start; x <= end; x++) {
                    blend_pixel(x, y, r, g, b, a, true);
                }
                break;
            case PixelFormat::RGB565:
                uint16_t color = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
                for (int64_t x = start; x <= end; x++) {
                    back_buffer[index] = color & 0xFF;
                    back_buffer[index + 1] = color >> 8;
                    index += 2;
                }
                break;
            case PixelFormat::GRAY8:
                uint8_t gray = static_cast<uint8_t>((r * 0.3f + g * 0.59f + b * 0.11f));
                std::fill_n(back_buffer.begin() + index, end - start + 1, gray);
                break;
        }
    }

    // Vertical line drawing
    void draw_vline(int64_t x, int64_t y1, int64_t y2, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        if (!is_initialized || x < clip_rect.x || x >= clip_rect.x + clip_rect.w) return;
        int64_t start = std::max(y1, clip_rect.y);
        int64_t end = std::min(y2, clip_rect.y + clip_rect.h - 1);
        if (start > end) return;

        size_t index = (start * display_config.width + x) * display_config.bytes_per_pixel;
        switch (display_config.format) {
            case PixelFormat::RGBA8888:
                for (int64_t y = start; y <= end; y++) {
                    blend_pixel(x, y, r, g, b, a);
                    index += display_config.width * 4;
                }
                break;
            case PixelFormat::ARGB8888:
                for (int64_t y = start; y <= end; y++) {
                    blend_pixel(x, y, r, g, b, a, true);
                    index += display_config.width * 4;
                }
                break;
            case PixelFormat::RGB565:
                uint16_t color = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
                for (int64_t y = start; y <= end; y++) {
                    back_buffer[index] = color & 0xFF;
                    back_buffer[index + 1] = color >> 8;
                    index += display_config.width * 2;
                }
                break;
            case PixelFormat::GRAY8:
                uint8_t gray = static_cast<uint8_t>((r * 0.3f + g * 0.59f + b * 0.11f));
                for (int64_t y = start; y <= end; y++) {
                    back_buffer[index] = gray;
                    index += display_config.width;
                }
                break;
        }
    }

public:
    Renderer(int64_t width = 1920, int64_t height = 1080, PixelFormat format = PixelFormat::RGBA8888) {
        initialize(width, height, format);
    }

    void initialize(int64_t width, int64_t height, PixelFormat format = PixelFormat::RGBA8888) {
        if (width <= 0 || height <= 0) {
            throw std::invalid_argument("Display dimensions must be positive");
        }
        display_config.width = width;
        display_config.height = height;
        display_config.format = format;
        display_config.bytes_per_pixel = (format == PixelFormat::RGBA8888 || format == PixelFormat::ARGB8888) ? 4 :
                                         (format == PixelFormat::RGB565) ? 2 : 1;
        front_buffer.assign(width * height * display_config.bytes_per_pixel, 0);
        back_buffer.assign(width * height * display_config.bytes_per_pixel, 0);
        clip_rect = {0, 0, width, height};
        is_initialized = true;
    }

    void set_blend_mode(BlendMode mode) {
        current_blend_mode = mode;
    }

    void swap_buffers() {
        std::swap(front_buffer, back_buffer);
    }

    bool send_to_display(uint64_t display_port_address) {
        if (!is_initialized) {
            std::cerr << "Error: Renderer not initialized" << std::endl;
            return false;
        }
        try {
            volatile uint8_t* port = reinterpret_cast<volatile uint8_t*>(display_port_address);
            std::copy(front_buffer.begin(), front_buffer.end(), port);
            last_display_port = display_port_address;
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Error in send_to_display: " << e.what() << std::endl;
            return false;
        }
    }

    void clear(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 255) {
        if (!is_initialized) return;
        switch (display_config.format) {
            case PixelFormat::RGBA8888:
                for (size_t i = 0; i < back_buffer.size(); i += 4) {
                    back_buffer[i] = r;
                    back_buffer[i + 1] = g;
                    back_buffer[i + 2] = b;
                    back_buffer[i + 3] = a;
                }
                break;
            case PixelFormat::ARGB8888:
                for (size_t i = 0; i < back_buffer.size(); i += 4) {
                    back_buffer[i] = a;
                    back_buffer[i + 1] = r;
                    back_buffer[i + 2] = g;
                    back_buffer[i + 3] = b;
                }
                break;
            case PixelFormat::RGB565:
                uint16_t color = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
                uint8_t low = color & 0xFF, high = color >> 8;
                for (size_t i = 0; i < back_buffer.size(); i += 2) {
                    back_buffer[i] = low;
                    back_buffer[i + 1] = high;
                }
                break;
            case PixelFormat::GRAY8:
                uint8_t gray = static_cast<uint8_t>((r * 0.3f + g * 0.59f + b * 0.11f));
                std::fill(back_buffer.begin(), back_buffer.end(), gray);
                break;
        }
    }

    void draw_pixel(int64_t x, int64_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
        if (!is_initialized || !is_in_clip(x, y)) return;
        size_t index = (y * display_config.width + x) * display_config.bytes_per_pixel;
        switch (display_config.format) {
            case PixelFormat::RGBA8888:
                blend_pixel(x, y, r, g, b, a);
                break;
            case PixelFormat::ARGB8888:
                blend_pixel(x, y, r, g, b, a, true);
                break;
            case PixelFormat::RGB565:
                uint16_t color = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
                back_buffer[index] = color & 0xFF;
                back_buffer[index + 1] = color >> 8;
                break;
            case PixelFormat::GRAY8:
                back_buffer[index] = static_cast<uint8_t>((r * 0.3f + g * 0.59f + b * 0.11f));
                break;
        }
    }

    void draw_line(int64_t x0, int64_t y0, int64_t x1, int64_t y1, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
        if (!is_initialized) return;
        int64_t dx = std::abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
        int64_t dy = -std::abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
        int64_t err = dx + dy;
        while (true) {
            draw_pixel(x0, y0, r, g, b, a);
            if (x0 == x1 && y0 == y1) break;
            int64_t e2 = 2 * err;
            if (e2 >= dy) { err += dy; x0 += sx; }
            if (e2 <= dx) { err += dx; y0 += sy; }
        }
    }

    void draw_line_aa(int64_t x0, int64_t y0, int64_t x1, int64_t y1, uint8_t r, uint8_t g, uint8_t b) {
        if (!is_initialized) return;
        bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);
        if (steep) { std::swap(x0, y0); std::swap(x1, y1); }
        if (x0 > x1) { std::swap(x0, x1); std::swap(y0, y1); }
        int64_t dx = x1 - x0, dy = y1 - y0;
        float gradient = (dx == 0) ? 1.0f : static_cast<float>(dy) / dx;

        int64_t xend = round(x0);
        float yend = y0 + gradient * (xend - x0), xgap = 1.0f - fpart(x0 + 0.5f);
        int64_t xpxl1 = xend, ypxl1 = ipart(yend);
        if (steep) {
            blend_pixel_aa(ypxl1, xpxl1, r, g, b, static_cast<uint8_t>((1.0f - fpart(yend)) * xgap * 255));
            blend_pixel_aa(ypxl1 + 1, xpxl1, r, g, b, static_cast<uint8_t>(fpart(yend) * xgap * 255));
        } else {
            blend_pixel_aa(xpxl1, ypxl1, r, g, b, static_cast<uint8_t>((1.0f - fpart(yend)) * xgap * 255));
            blend_pixel_aa(xpxl1, ypxl1 + 1, r, g, b, static_cast<uint8_t>(fpart(yend) * xgap * 255));
        }
        float intery = yend + gradient;

        xend = round(x1);
        yend = y1 + gradient * (xend - x1);
        xgap = fpart(x1 + 0.5f);
        int64_t xpxl2 = xend, ypxl2 = ipart(yend);
        if (steep) {
            blend_pixel_aa(ypxl2, xpxl2, r, g, b, static_cast<uint8_t>((1.0f - fpart(yend)) * xgap * 255));
            blend_pixel_aa(ypxl2 + 1, xpxl2, r, g, b, static_cast<uint8_t>(fpart(yend) * xgap * 255));
        } else {
            blend_pixel_aa(xpxl2, ypxl2, r, g, b, static_cast<uint8_t>((1.0f - fpart(yend)) * xgap * 255));
            blend_pixel_aa(xpxl2, ypxl2 + 1, r, g, b, static_cast<uint8_t>(fpart(yend) * xgap * 255));
        }

        if (steep) {
            for (int64_t x = xpxl1 + 1; x < xpxl2; x++) {
                blend_pixel_aa(ipart(intery), x, r, g, b, static_cast<uint8_t>((1.0f - fpart(intery)) * 255));
                blend_pixel_aa(ipart(intery) + 1, x, r, g, b, static_cast<uint8_t>(fpart(intery) * 255));
                intery += gradient;
            }
        } else {
            for (int64_t x = xpxl1 + 1; x < xpxl2; x++) {
                blend_pixel_aa(x, ipart(intery), r, g, b, static_cast<uint8_t>((1.0f - fpart(intery)) * 255));
                blend_pixel_aa(x, ipart(intery) + 1, r, g, b, static_cast<uint8_t>(fpart(intery) * 255));
                intery += gradient;
            }
        }
    }

    void blend_pixel(int64_t x, int64_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a, bool argb = false) {
        if (!is_initialized || !is_in_clip(x, y)) return;
        size_t index = (y * display_config.width + x) * display_config.bytes_per_pixel;
        if (display_config.format == PixelFormat::RGBA8888 || display_config.format == PixelFormat::ARGB8888) {
            uint8_t bg_r, bg_g, bg_b, bg_a;
            if (argb) {
                bg_a = back_buffer[index];
                bg_r = back_buffer[index + 1];
                bg_g = back_buffer[index + 2];
                bg_b = back_buffer[index + 3];
            } else {
                bg_r = back_buffer[index];
                bg_g = back_buffer[index + 1];
                bg_b = back_buffer[index + 2];
                bg_a = back_buffer[index + 3];
            }
            uint8_t out_r, out_g, out_b;
            switch (current_blend_mode) {
                case BlendMode::NORMAL:
                    out_r = (a * r + (255 - a) * bg_r) / 255;
                    out_g = (a * g + (255 - a) * bg_g) / 255;
                    out_b = (a * b + (255 - a) * bg_b) / 255;
                    break;
                case BlendMode::ADDITIVE:
                    out_r = std::min(255, bg_r + r);
                    out_g = std::min(255, bg_g + g);
                    out_b = std::min(255, bg_b + b);
                    break;
                case BlendMode::MULTIPLY:
                    out_r = (bg_r * r) / 255;
                    out_g = (bg_g * g) / 255;
                    out_b = (bg_b * b) / 255;
                    break;
                case BlendMode::SUBTRACTIVE:
                    out_r = std::max(0, bg_r - r);
                    out_g = std::max(0, bg_g - g);
                    out_b = std::max(0, bg_b - b);
                    break;
            }
            if (argb) {
                back_buffer[index] = 255;
                back_buffer[index + 1] = out_r;
                back_buffer[index + 2] = out_g;
                back_buffer[index + 3] = out_b;
            } else {
                back_buffer[index] = out_r;
                back_buffer[index + 1] = out_g;
                back_buffer[index + 2] = out_b;
                back_buffer[index + 3] = 255;
            }
        }
    }

    void blend_pixel_aa(int64_t x, int64_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t coverage) {
        if (!is_initialized || !is_in_clip(x, y)) return;
        size_t index = (y * display_config.width + x) * display_config.bytes_per_pixel;
        switch (display_config.format) {
            case PixelFormat::RGBA8888:
            case PixelFormat::ARGB8888:
                blend_pixel(x, y, r, g, b, coverage, display_config.format == PixelFormat::ARGB8888);
                break;
            case PixelFormat::RGB565:
                uint16_t bg_color = back_buffer[index] | (back_buffer[index + 1] << 8);
                uint8_t bg_r = ((bg_color >> 11) & 0x1F) << 3;
                uint8_t bg_g = ((bg_color >> 5) & 0x3F) << 2;
                uint8_t bg_b = (bg_color & 0x1F) << 3;
                uint8_t out_r = (coverage * r + (255 - coverage) * bg_r) / 255;
                uint8_t out_g = (coverage * g + (255 - coverage) * bg_g) / 255;
                uint8_t out_b = (coverage * b + (255 - coverage) * bg_b) / 255;
                uint16_t color = ((out_r >> 3) << 11) | ((out_g >> 2) << 5) | (out_b >> 3);
                back_buffer[index] = color & 0xFF;
                back_buffer[index + 1] = color >> 8;
                break;
            case PixelFormat::GRAY8:
                uint8_t bg_gray = back_buffer[index];
                uint8_t gray = static_cast<uint8_t>((r * 0.3f + g * 0.59f + b * 0.11f));
                back_buffer[index] = (coverage * gray + (255 - coverage) * bg_gray) / 255;
                break;
        }
    }

    void draw_triangle(int64_t x0, int64_t y0, int64_t x1, int64_t y1, int64_t x2, int64_t y2,
                       uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
        draw_line(x0, y0, x1, y1, r, g, b, a);
        draw_line(x1, y1, x2, y2, r, g, b, a);
        draw_line(x2, y2, x0, y0, r, g, b, a);
    }

    void fill_triangle(int64_t x0, int64_t y0, int64_t x1, int64_t y1, int64_t x2, int64_t y2,
                       uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
        if (!is_initialized) return;
        if (y0 > y1) { std::swap(x0, x1); std::swap(y0, y1); }
        if (y1 > y2) { std::swap(x1, x2); std::swap(y1, y2); }
        if (y0 > y1) { std::swap(x0, x1); std::swap(y0, y1); }

        if (y0 == y2) return;

        auto draw_span = [&](int64_t y, int64_t x_start, int64_t x_end) {
            if (x_start > x_end) std::swap(x_start, x_end);
            draw_hline(x_start, x_end, y, r, g, b, a);
        };

        if (y0 == y1) {
            for (int64_t y = y0; y <= y2; y++) {
                int64_t x_left = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
                int64_t x_right = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
                draw_span(y, x_left, x_right);
            }
        } else if (y1 == y2) {
            for (int64_t y = y0; y <= y1; y++) {
                int64_t x_left = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
                int64_t x_right = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
                draw_span(y, x_left, x_right);
            }
        } else {
            int64_t x_mid = x0 + (x2 - x0) * (y1 - y0) / (y2 - y0);
            for (int64_t y = y0; y <= y1; y++) {
                int64_t x_left = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
                int64_t x_right = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
                draw_span(y, x_left, x_right);
            }
            for (int64_t y = y1; y <= y2; y++) {
                int64_t x_left = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
                int64_t x_right = x_mid + (x2 - x_mid) * (y - y1) / (y2 - y1);
                draw_span(y, x_left, x_right);
            }
        }
    }

    void draw_ellipse(int64_t xc, int64_t yc, int64_t a, int64_t b, uint8_t r, uint8_t g, uint8_t b, uint8_t a_) {
        if (!is_initialized || a < 0 || b < 0) return;
        int64_t x = 0, y = b;
        int64_t aa = a * a, bb = b * b;
        int64_t d1 = bb + aa * (-2 * b + 1);
        while (y >= 0 && x <= a) {
            draw_pixel(xc + x, yc + y, r, g, b, a_);
            draw_pixel(xc - x, yc + y, r, g, b, a_);
            draw_pixel(xc + x, yc - y, r, g, b, a_);
            draw_pixel(xc - x, yc - y, r, g, b, a_);
            if (d1 < 0) {
                x++;
                d1 += bb * (2 * x + 1);
            } else {
                y--;
                d1 += bb * (2 * x + 1) + aa * (-2 * y + 1);
            }
        }
    }

    void draw_ellipse_aa(int64_t xc, int64_t yc, int64_t a, int64_t b, uint8_t r, uint8_t g, uint8_t b) {
        if (!is_initialized || a < 0 || b < 0) return;
        for (int64_t x = -a; x <= a; x++) {
            for (int64_t y = -b; y <= b; y++) {
                float dx = static_cast<float>(x) / a;
                float dy = static_cast<float>(y) / b;
                float dist = std::sqrt(dx * dx + dy * dy);
                if (dist <= 1.0f) {
                    float coverage = std::min(1.0f, 1.0f - (dist - 1.0f + 0.5f));
                    if (coverage > 0) {
                        blend_pixel_aa(xc + x, yc + y, r, g, b, static_cast<uint8_t>(coverage * 255));
                    }
                }
            }
        }
    }

    void fill_ellipse(int64_t xc, int64_t yc, int64_t a, int64_t b, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        if (!is_initialized || a < 0 || b < 0) return;
        for (int64_t dy = -b; dy <= b; dy++) {
            int64_t yy = yc + dy;
            if (yy < clip_rect.y || yy >= clip_rect.y + clip_rect.h) continue;
            double x_span = a * std::sqrt(1.0 - (dy * dy) / (double)(b * b));
            int64_t x_min = std::max(clip_rect.x, static_cast<int64_t>(std::ceil(xc - x_span)));
            int64_t x_max = std::min(clip_rect.x + clip_rect.w - 1, static_cast<int64_t>(std::floor(xc + x_span)));
            if (x_min <= x_max) {
                draw_hline(x_min, x_max, yy, r, g, b, a);
            }
        }
    }

    void draw_circle(int64_t xc, int64_t yc, int64_t radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        draw_ellipse(xc, yc, radius, radius, r, g, b, a);
    }

    void draw_circle_aa(int64_t xc, int64_t yc, int64_t radius, uint8_t r, uint8_t g, uint8_t b) {
        draw_ellipse_aa(xc, yc, radius, radius, r, g, b);
    }

    void fill_circle(int64_t xc, int64_t yc, int64_t radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        fill_ellipse(xc, yc, radius, radius, r, g, b, a);
    }

    void draw_rect(int64_t x, int64_t y, int64_t w, int64_t h, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        if (!is_initialized || w <= 0 || h <= 0) return;
        draw_hline(x, x + w - 1, y, r, g, b, a);
        draw_hline(x, x + w - 1, y + h - 1, r, g, b, a);
        draw_vline(x, y, y + h - 1, r, g, b, a);
        draw_vline(x + w - 1, y, y + h - 1, r, g, b, a);
    }

    void fill_rect(int64_t x, int64_t y, int64_t w, int64_t h, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        if (!is_initialized || w <= 0 || h <= 0) return;
        int64_t x_start = std::max(x, clip_rect.x);
        int64_t x_end = std::min(x + w - 1, clip_rect.x + clip_rect.w - 1);
        int64_t y_start = std::max(y, clip_rect.y);
        int64_t y_end = std::min(y + h - 1, clip_rect.y + clip_rect.h - 1);
        if (x_start > x_end || y_start > y_end) return;

        for (int64_t yy = y_start; yy <= y_end; yy++) {
            draw_hline(x_start, x_end, yy, r, g, b, a);
        }
    }

    void draw_polygon(const std::vector<std::pair<int64_t, int64_t>>& vertices,
                      uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
        if (!is_initialized || vertices.size() < 2) return;
        for (size_t i = 0; i < vertices.size() - 1; i++) {
            draw_line(vertices[i].first, vertices[i].second,
                      vertices[i + 1].first, vertices[i + 1].second, r, g, b, a);
        }
        draw_line(vertices.back().first, vertices.back().second,
                  vertices.front().first, vertices.front().second, r, g, b, a);
    }

    void fill_polygon(const std::vector<std::pair<int64_t, int64_t>>& vertices,
                      uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
        if (!is_initialized || vertices.size() < 3) return;
        int64_t min_y = vertices[0].second, max_y = vertices[0].second;
        for (const auto& v : vertices) {
            min_y = std::min(min_y, v.second);
            max_y = std::max(max_y, v.second);
        }
        min_y = std::max(min_y, clip_rect.y);
        max_y = std::min(max_y, clip_rect.y + clip_rect.h - 1);

        struct Edge {
            int64_t x, y_max, dx, dy;
            Edge(int64_t x_, int64_t y_max_, int64_t dx_, int64_t dy_) : x(x_), y_max(y_max_), dx(dx_), dy(dy_) {}
        };
        std::vector<Edge> edges;
        for (size_t i = 0; i < vertices.size(); i++) {
            int64_t x0 = vertices[i].first, y0 = vertices[i].second;
            int64_t x1 = vertices[(i + 1) % vertices.size()].first;
            int64_t y1 = vertices[(i + 1) % vertices.size()].second;
            if (y0 == y1) continue;
            if (y0 > y1) { std::swap(x0, x1); std::swap(y0, y1); }
            edges.emplace_back(x0, y1, x1 - x0, y1 - y0);
        }

        for (int64_t y = min_y; y <= max_y; y++) {
            std::vector<int64_t> active_x;
            for (const auto& e : edges) {
                if (y >= e.y_max || y < min_y) continue;
                int64_t x = e.x + (y - min_y) * e.dx / e.dy;
                active_x.push_back(x);
            }
            std::sort(active_x.begin(), active_x.end());
            for (size_t i = 0; i < active_x.size(); i += 2) {
                if (i + 1 < active_x.size()) {
                    draw_hline(active_x[i], active_x[i + 1], y, r, g, b, a);
                }
            }
        }
    }

    void draw_arc(int64_t xc, int64_t yc, int64_t radius, float start_angle, float end_angle,
                  uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
        if (!is_initialized || radius < 0) return;
        float theta = start_angle;
        float dtheta = 1.0f / radius;
        int64_t x0 = xc + static_cast<int64_t>(radius * std::cos(theta));
        int64_t y0 = yc + static_cast<int64_t>(radius * std::sin(theta));
        while (theta <= end_angle) {
            int64_t x1 = xc + static_cast<int64_t>(radius * std::cos(theta));
            int64_t y1 = yc + static_cast<int64_t>(radius * std::sin(theta));
            draw_line(x0, y0, x1, y1, r, g, b, a);
            x0 = x1;
            y0 = y1;
            theta += dtheta;
        }
    }

    void draw_bezier(int64_t x0, int64_t y0, int64_t x1, int64_t y1, int64_t x2, int64_t y2,
                     uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255, int segments = 20) {
        if (!is_initialized) return;
        int64_t prev_x = x0, prev_y = y0;
        for (int i = 1; i <= segments; i++) {
            float t = static_cast<float>(i) / segments;
            float u = 1.0f - t;
            int64_t x = static_cast<int64_t>(u * u * x0 + 2 * u * t * x1 + t * t * x2);
            int64_t y = static_cast<int64_t>(u * u * y0 + 2 * u * t * y1 + t * t * y2);
            draw_line(prev_x, prev_y, x, y, r, g, b, a);
            prev_x = x;
            prev_y = y;
        }
    }

    void draw_text(int64_t x, int64_t y, const std::string& text, const Font& font,
                   uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
        if (!is_initialized) return;
        int64_t current_x = x;
        for (char c : text) {
            auto it = font.bitmap_data.find(c);
            if (it == font.bitmap_data.end()) it = default_font_data.find(c);
            if (it != default_font_data.end()) {
                const std::vector<uint8_t>& bitmap = it->second;
                for (int64_t row = 0; row < font.size; row++) {
                    uint8_t byte = bitmap[row];
                    for (int64_t col = 0; col < font.size; col++) {
                        if (byte & (1 << (font.size - 1 - col))) {
                            draw_pixel(current_x + col, y + row, r, g, b, a);
                        }
                    }
                }
                current_x += font.size;
            }
        }
    }

    void draw_image(int64_t x, int64_t y, const uint8_t* image_data, int64_t image_width, int64_t image_height,
                    PixelFormat image_format) {
        if (!is_initialized || !image_data || image_width <= 0 || image_height <= 0) return;
        int64_t src_x_start = 0, src_y_start = 0;
        int64_t dest_x_start = x, dest_y_start = y;
        int64_t copy_w = image_width, copy_h = image_height;

        if (x < clip_rect.x) { src_x_start = clip_rect.x - x; dest_x_start = clip_rect.x; copy_w -= src_x_start; }
        if (y < clip_rect.y) { src_y_start = clip_rect.y - y; dest_y_start = clip_rect.y; copy_h -= src_y_start; }
        if (dest_x_start + copy_w > clip_rect.x + clip_rect.w) copy_w = clip_rect.x + clip_rect.w - dest_x_start;
        if (dest_y_start + copy_h > clip_rect.y + clip_rect.h) copy_h = clip_rect.y + clip_rect.h - dest_y_start;
        if (copy_w <= 0 || copy_h <= 0) return;

        uint32_t src_bpp = (image_format == PixelFormat::RGBA8888 || image_format == PixelFormat::ARGB8888) ? 4 :
                           (image_format == PixelFormat::RGB565) ? 2 : 1;
        for (int64_t i = 0; i < copy_h; i++) {
            for (int64_t j = 0; j < copy_w; j++) {
                int64_t src_x = src_x_start + j, src_y = src_y_start + i;
                int64_t dest_x = dest_x_start + j, dest_y = dest_y_start + i;
                size_t src_index = (src_y * image_width + src_x) * src_bpp;
                uint8_t r, g, b, a = 255;
                switch (image_format) {
                    case PixelFormat::RGBA8888:
                        r = image_data[src_index];
                        g = image_data[src_index + 1];
                        b = image_data[src_index + 2];
                        a = image_data[src_index + 3];
                        break;
                    case PixelFormat::ARGB8888:
                        a = image_data[src_index];
                        r = image_data[src_index + 1];
                        g = image_data[src_index + 2];
                        b = image_data[src_index + 3];
                        break;
                    case PixelFormat::RGB565:
                        uint16_t color = image_data[src_index] | (image_data[src_index + 1] << 8);
                        r = (color >> 11) << 3;
                        g = ((color >> 5) & 0x3F) << 2;
                        b = (color & 0x1F) << 3;
                        break;
                    case PixelFormat::GRAY8:
                        r = g = b = image_data[src_index];
                        break;
                }
                draw_pixel(dest_x, dest_y, r, g, b, a);
            }
        }
    }

    void set_clip_rect(int64_t x, int64_t y, int64_t w, int64_t h) {
        clip_rect = {std::max(int64_t(0), x), std::max(int64_t(0), y),
                     std::min(w, display_config.width - std::max(int64_t(0), x)),
                     std::min(h, display_config.height - std::max(int64_t(0), y))};
    }

    bool save_to_file(const std::string& filename) {
        if (!is_initialized) return false;
        std::ofstream file(filename, std::ios::binary);
        if (!file) return false;
        if (display_config.format == PixelFormat::RGBA8888 || display_config.format == PixelFormat::ARGB8888) {
            file << "P6\n" << display_config.width << " " << display_config.height << "\n255\n";
            for (size_t i = 0; i < back_buffer.size(); i += 4) {
                uint8_t r = (display_config.format == PixelFormat::ARGB8888) ? back_buffer[i + 1] : back_buffer[i];
                uint8_t g = (display_config.format == PixelFormat::ARGB8888) ? back_buffer[i + 2] : back_buffer[i + 1];
                uint8_t b = (display_config.format == PixelFormat::ARGB8888) ? back_buffer[i + 3] : back_buffer[i + 2];
                file.put(static_cast<char>(r));
                file.put(static_cast<char>(g));
                file.put(static_cast<char>(b));
            }
        } else if (display_config.format == PixelFormat::GRAY8) {
            file << "P5\n" << display_config.width << " " << display_config.height << "\n255\n";
            file.write(reinterpret_cast<const char*>(back_buffer.data()), back_buffer.size());
        }
        return file.good();
    }

    int64_t get_width() const { return display_config.width; }
    int64_t get_height() const { return display_config.height; }
    size_t get_buffer_size() const { return back_buffer.size(); }
    uint8_t* get_frame_buffer() { return back_buffer.data(); }
};

std::map<char, std::vector<uint8_t>> Renderer::default_font_data = {
    {'A', {0x00, 0x18, 0x24, 0x42, 0x7E, 0x42, 0x42, 0x00}},
    {'B', {0x00, 0x7C, 0x42, 0x7C, 0x42, 0x42, 0x7C, 0x00}},
    {'C', {0x00, 0x3C, 0x42, 0x40, 0x40, 0x42, 0x3C, 0x00}}
};

} // namespace graphics_primitive

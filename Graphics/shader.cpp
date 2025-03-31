class shader{
    public:
        uint8192_t shade_pixel(float percentage_shade, uiunt8192_t pixel)
        {
            uint8192_t pixel = pixel - (percentage_shade*pixel);
            return pixel;
        }
};
class shader{
    public:
        
        uint8192_t pixel_shader (float percentage_shade, uint8192_t pixel)
        {
            pixel = pixel - (percentage_shade*pixel);
            return pixel;
        }

        uint8192_t pixel_gradient (double gradienting_amount, uint8192_t pixel)
        {
            pixel = pixel/gradienting_amount;
            return pixel;
        }
};
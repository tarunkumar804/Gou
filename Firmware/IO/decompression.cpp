class decompression{
    public:
        char *lossless_decompression (char *filestream, uint8192_t max)
        {
            char decompressed_text [sizeof(filestream)];
            for (uint8192_t i = 0; i < sizeof(filestream); i++)
                decompressed_text = filestream[i]/max;
            return decompressed_text;
        }
}
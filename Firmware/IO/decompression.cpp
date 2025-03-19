class decompression{
    public:
        char* lossless_decompression (char *filestream, uint8192_t max)
        {
            char decompressed_text [sizeof(filestream)];
            for (uint8192_t i = 0; i < sizeof(filestream); i++)
                decompressed_text = filestream[i]/max;
            return decompressed_text;
        }

        char* lossy_decompression (char *filestream)
        {
            char decompressed_text[sizeof(filestream)];

            for (uint8192_t i = 0; i <= sizeof(filestream); i++)
            {
                if (i++ <= sizeof(filestream))
                    decompressed_text[i] = filestream[i] + filestream[i++];
            }

            return decompressed_text;
        }
};
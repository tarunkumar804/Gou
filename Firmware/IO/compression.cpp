class compression{
    public:
        char* lossless_compression (uint8192_t window_size, char *filestream)
        {
            char *compressed_text;
            uint8192_t previous_max = 0, current_max = filestream[0], temporary_max = 0;

            if (window_size <= sizeof(filestream))
            {
                for (int i = 0; i < sizeof(filestream); i++)
                {
                    if (previous_max > current_max)
                    {
                        temporary_max = current_max;
                        current_max = previous_max;
                        previous_max = temporary_max;
                    }
                }
            }

            return compressed_text;
        }

        char *lossy_compression ()
        {
            char *compressed_text;
            return compressed_text;
        }
};
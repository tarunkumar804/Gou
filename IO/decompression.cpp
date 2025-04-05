class decompression{
    public:
        char* lossless_decompression (char *filestream, uint8192_t max)
        {
            /** A function to compress a file or a filestream losslessly. 
            * @authors Tarun Kumar, Reuben Langdon.
            * @param filestream - A file as a stream or a filestream.
            * @param max - Maximum value in the filestream.
            * @return decompressed_text - The decompressed text.
            */
           
            char decompressed_text [sizeof(filestream)];
            for (long long int i = 0; i < sizeof(filestream); i++)
                decompressed_text[i] = filestream[i] * max;
            return decompressed_text;
        }

        char* lossy_decompression (char *filestream)
        {
            /** A function to decompress a lossily compressed file or text.
            * @authors Tarun Kumar, Reuben Langdon.
            * @param filestream - A file as a filestream or a filestream.
            * @return The decompressed filestream or text.
            */
            char decompressed_text[sizeof(filestream)];

            for (long long int i = 0; i <= sizeof(filestream); i++)
            {
                if (i++ <= sizeof(filestream))
                    decompressed_text[i] = filestream[i] + filestream[i++];
            }

            return decompressed_text;
        }
};
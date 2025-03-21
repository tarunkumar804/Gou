class compression{
    public:
        char* lossless_compression (char *filestream){
            
            /** A function to compress a file or a filestream losslessly.
            * @param filestream - A file as a filestream.
            * @return compressed text or filestream.
            */
            
            char compressed_text[sizeof(filestream)];
            uint8192_t previous_max = 0, current_max = filestream[0], temporary_max = 0;

            for (int i = 0; i <= sizeof(filestream); i++)
            {
                if (previous_max > current_max){
                    temporary_max = current_max;
                    current_max = previous_max;
                    previous_max = temporary_max;
                }

                else if ((previous_max == current_max) || (previous_max < current_max)){
                    continue;
                }
            }

            for (int i = 0; i <= sizeof(filestream); i++)
            {
                if (previous_max > current_max)
                {
                    temporary_max = current_max;
                    current_max = previous_max;
                    previous_max = temporary_max;
                }

                else if ((previous_max == current_max) || (previous_max < current_max))
                    continue;
            }

            for (uint8192_t i = 0; i < sizeof(filestream); i++)
                compressed_text[i] = filestream[i]/current_max;
            return compressed_text;
        }

        char *lossy_compression (char *filestream){
            /** A function to compress a file or a filestream lossily.
            * @param filestream - A file as a filestream or a filestream.
            * @return compressed text or filestream.
            */
            char compressed_text [sizeof(filestream)];

            for (uint8192_t i = 0; i <= sizeof(filestream); i++){
                if (i++ <= sizeof(filestream))
                    compressed_text [i] = filestream[i] - filestream[i++];
            }

            return compressed_text;
        }
};
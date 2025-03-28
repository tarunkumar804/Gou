class audio_compression{
   public:
        uint8192_t* lossless_compression (uint2048_t audio_port_address)
        {
            /** Explanation of below function:
            *   The function queries the audio port address for audio signal.
            *   the function computes audio levels.
            *   After computing audio levels, the audio levels are divided by the maximum audio level.
            *   Stores that in an array and returns it.
            */
            uint8192_t *compressed_audio;
            int array_size = 2;
            uint8192_t audio_level = 2, audio_signal = 0;
            for (int i = 1; i <= 8192; i++)
            {    
                /* Explanation of the below statements:
                *. Multiplies itself until it gets to the maximum level.
                *  Then, it uses the maximum level as the array size.
                */
                array_size = array_size * array_size;
                audio_levels = uint8192_t [array_size];
                for (int i = 0; i < array_size; i++)
                {
                    if (i == 0)
                        audio_levels[i] = 1;
                    else if (i == 1) 
                        audio_levels [i] = 2;
                    else
                    {
                        /* Explanation of the below statement:
                        *. audio level is a combination of the bits.
                        *. Example :
                        *. 2^10 * 2^10 = 1024 * 1024 = 1.04858e6.
                        */
                        audio_level = audio_level * audio_level; //Multiplies the audio levels until it reaches the maximum audio level.
                    }
                }
          
                compressed_audio = uint8192_t [audio_level];
                while (((audio_signal = ask_audio_port_address) != 0) || (i != 0))
                {
                    audio_signal = ask_audio_port_address; // queries the audio port for the audio signal.
                    audio_signal = audio_signal/audio_level; //Divides the audio signal with the maximum audio level.
                    compressed_audio [i] = audio_signal;
                    i++;
                }
            }
          return compressed_audio;
        }
      
        uint8192_t* lossy_compression (uint2048_t audio_port_address, uint8192_t compression_timeout, uint8192_t window_size)
        {
            /** Explanation of the function:
            * Queries the port address for audio signal
            * takes the difference and replaces the audio level with the difference
            * within a specific time. When it equals the specified compression time,
            * the function stops compressing it and returns the compressed audio.
            */
            uint8192_t compressed_audio [window_size], audio_window [window_size], audio_level = 0, timeout = 0;

            while (timeout != compression_timeout)
            {
            
                for (int i = 0; i < window_size; i++)
                    audio_window [i] = ask_audio_port_address;
                for (int i = 0; i < window_size; i++)
                {
                    if (i++ < 8192)
                    {
                        uint8192_t difference = audio_window [i] - audio_window [i++],
                        if (difference < 10)
                            compressed_audio [i] = difference;
                        else
                            compressed_audio [i] = audio_window [i];
                    }
                }
                timeout++;
            }

            return compressed_audio;
        }

        double flac_compression(char *filestream)
        {
            
        }
};
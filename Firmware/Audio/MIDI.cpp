class MIDI {
   public:
      uint8192_t* recieve_and_store_audio_signal (uint2048_t audio_port_address, uint8192_t window_size)
      {
        uint8192_t audio_window [window_size];
        
        for (uint8192_t index = 0; index < window_size; index++)
               audio_window [index];
        return audio_window;
      }

      uint8192_t** recieve_and_store_pin_data (uint8192_t MIDI_port1_address, uint8192_t MIDI_port2_address, uint8192_t MIDI_port3_address, uint8192_t MIDI_port4_address, uint8192_t MIDI_port5_address, uint8192_t number_of_samples)
      {
          uint8192_t MIDI_data[10][number_of_samples];

          for (int i = 0; i < 10; i++)
             for (int j = 0; j < number_of_samples; i++)
             {
                  if (i == 0)
                      MIDI_data[i][j] =ask_MIDI_port1_address;
                  else if (i == 1)
                      MIDI_data [i][j] = ask_MIDI_port2_address;
                  else if (i == 2)
                       MIDI_data [i][j] = ask_MIDI_port3_address;
                  else if (i == 3)
                        MIDI_data [i][j] = ask_MIDI_port4_address;
                  else if (i == 4)
                        MIDI_data [i][j] = ask_MIDI_port5_address;

             }
        return MIDI_data;
      }
};
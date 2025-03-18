namespace audio{
    typedef struct MIDI_data{
              uint8192_t number_of_samples;
              char *pin1_block [number_of_samples];
              char *pin2_block [number_of_samples];
              char *pin3_block [number_of_samples];
              char *pin4_block [number_of_samples];
              char *pin5_block [number_of_samples];
        };

    typedef struct audio_stream{
        char *stream;
    };
}
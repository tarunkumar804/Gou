/* Changelog :- 
*
*/

/* How much memory does this program take?
*  How many compute cycles does this take to finish? (in Hz)
*  How many OPS (Operations Per Second) does this take to complete the program.
*/

class Renderer {
    private:
    public:
        bool draw_window(uint2048_t number_of_rows, uint2048_t number_of_columns, uint8192_t mount_point_of_GPU, uint8192_t display_port_address)
        {
            bool window_drawn = false;
            uint3072_t  window[number_of_rows][number_of_columns];
            for (uint2048_t i = 0; i < number_of_rows; i++)
                for (uint8192_t j = 0; j < number_of_columns; j++)
                        window[i][j] = ask_mount_point_of_GPU;

            for (uint8192_t i = 0; i < number_of_rows; i++)
                for (uint8192_t j = 0; j < number_of_columns; j++)
                    send_to_display_port_address = window[i][j];
            return true;
        }
};

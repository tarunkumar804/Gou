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

        bool draw_window(uint2048_t number_of_rows, uint2048_t number_of_columns, uint8192_t monitor_mount_point)
        {
            /** A function to draw a window on the display.
            * @param number_of_rows - Number of rows in the image matrix.
            * @param number_of_columns - Number of columns in the image matrix.
            * @param monitor_mount_point - Mount point address of Monitor in RAM.
            * @return Image to draw on screen.
            */

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
        
        bool render_frames (frame frames[], long long int delay_in_rendering)
        {
            for 
        }
};

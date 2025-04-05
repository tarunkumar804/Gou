class graphs{
    map* generate_map(long long int map_length, long long int map_breadth, long long int vertex_interval)
    {
        map m = new map();
        m.map_length = this.map_length;
        m.map_breadth = this.map_breadth;
        m = new map(); //To resize the map.

        for (long long int row = 0; row < map_length; row++)
            for (long long int column = 0; column < map_breadth; column++)
            {
                if ((row+column % vertex_interval) == 0)
                    m.grid[row][column] = 'x';   
            }
        return m;
    }
};
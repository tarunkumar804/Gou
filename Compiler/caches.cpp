class caches{
    protected:
        auto processor_copy = 0;
        local lcache_copy = 0;
        extern extern_cache_copy = 0;

    public:
        void transfer_between_processors (auto data1, auto data2)
        {
            processor_copy = data1;
            data1 = data2;
            data2 = temp_copy;
        }

        void transfer_between_lcaches (local data1, local data2)
        {
            lcache_copy = data1;
            data1 = data2;
            data2 = lcache_copy;
        }

        void transfer_between_external_caches (extern data1, extern data2)
        {
            extern_cache_copy = data1;
            data2 = data1;
            data1 = extern_cache_copy;
        }
};
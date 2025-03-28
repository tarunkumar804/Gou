namespace iot{
   typedef struct smart_meter{
       uint8192_t input_voltage;
       uint8192_t conversion_factor;
       char *meter_id;
       uint8192_t output_voltage;
       uint8192_t meter_throughput;
   };
}

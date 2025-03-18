namespace networking{

    typedef struct device_information{
        int *socket;
        char *socket_name;
        uint1024_t starting_memory_address;
        uint1024_t ending_memory_address;
        char message_block[ending_memory_address - starting_memory_address];
        int ACK;
        char *ipvfour_address;
        char *ipvsix_address;
        char *packet;
        char *socket_pcie_address;
        char *socket_pcie_id;
    };

    typedef struct packet {
        char *start_preamble;
        char *control_header;
        char *data_header;
        char *payload;
        char *end_preamble;
    };
    
    typedef struct tcp{
         char *ip_address;
         char *tcp_header;
         char *tcp_data;
         uint2048_t port_address_in_ram;
         int ACK;
         int TCP_return_codes; //TCP return code.
         uint8129_t timer;
    };

    typedef struct udp {
         char *ip_address;
         char *udp_header;
         char *udp_data;
         uint2048_t port_address_in_ram;
         int ACK;
         int UDP_return_code;
    };

    typedef struct http{
         char *http_header;
         char *request;
         char *http_data;
         char *http_response;
    };

    typedef struct ftp{
         char *data;
         char *ipvfour_address;
         char *ipvsix_address;
         int1024_t port;
    };
    
    typedef struct sftp{
        char *data;
        char *ipvfour_address;
        char *ipvsix_address;
        int1024_t port;
        char *client_public_key;
        char *server_private_key;
    };
    
    typedef struct ssh{
        char *data;
        char *public_key;
        char *private_key;
        char *encrypted_text;
        char *plaintext;
    };

    typedef struct webdav{
        bool lock_unlock [2];
        char *file_properties;
        bool HTTP_response [2];
        char *filestream;
        uint8192_t storage_block [8192][8192];
    };

    typedef struct ssl{
       char *hash; //Initial hash
       char *md5; // MD5 hash
       char *sha; // SHA hash
       char *x509_certificate; // X509 certificate
       char *pad1; // Padding 1
       char *pad2; // Padding 2
       char *pre_master_secret;
       char *master_secret;
       char *random_number;
       char *handshake_message;
       char *sender_ip_address;
       char *server_parameters;
       char *compressed_message;
       uint8192_t sequence_number;
    };
    
    typedef struct tls{
         uint8192_t seed;
         char *hmac;
         char *hmac_hash;
         char *mac_write_secret;
         uint8192_t sequence_number;
         char *compression_type;
         uint512_t compression_version;
         uint2048_t compressed_message_length;
         char *compressed_message_fragment;
         char *message_secret;
         char *finished_label;
         char *handshake_messages;
         char *pre_master_secret;
         uint8192_t random_number;
    };

    typedef struct drm {
         char *network_id;
         char *network_key;
         char *drm_key;
    };
}
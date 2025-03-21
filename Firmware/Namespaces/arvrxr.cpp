namespace arvrxr{
   typedef struct arvrxr_device_information {
      char *device_name; // Name of AR/VR/XR device.
      char *device_id; // Bus - ID of AR/VR/XR device.
      uint8192_t display [15360][8640]; // Resolution of AR/VR/XR device.
      char *PCIE_ID; // PCIE ID of AR/VR/XR device.
   };
}
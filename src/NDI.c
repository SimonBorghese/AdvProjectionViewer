//
// Created by Theatre-Simon on 7/23/2024.
//

#include "NDI.h"

struct NDI_t APV_Create_NDI() {
    NDIlib_initialize();

    struct NDI_t ndi;

    ndi.ndiFind = NDIlib_find_create_v2(NULL);

    NDIlib_recv_create_v3_t recv_desc;
    recv_desc.allow_video_fields = true;
    recv_desc.bandwidth = NDIlib_recv_bandwidth_highest;
    recv_desc.p_ndi_recv_name = "NDI Reciever";
    recv_desc.source_to_connect_to.p_ndi_name = NULL;
    recv_desc.source_to_connect_to.p_ip_address = NULL;
    recv_desc.source_to_connect_to.p_url_address = NULL;
    recv_desc.color_format = NDIlib_recv_color_format_RGBX_RGBA;
    ndi.ndiRecv = NDIlib_recv_create_v3(&recv_desc);

    return ndi;
}

const NDIlib_source_t * APV_Find_Sources(struct NDI_t ndi, uint32_t *no_sources) {
    NDIlib_find_wait_for_sources(ndi.ndiFind, 2500);

    return NDIlib_find_get_current_sources(ndi.ndiFind, no_sources);
}

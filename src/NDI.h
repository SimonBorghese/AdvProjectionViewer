//
// Created by Theatre-Simon on 7/23/2024.
//

#ifndef NDI_H
#define NDI_H
#include <Processing.NDI.Lib.h>

struct NDI_t {
    NDIlib_find_instance_t ndiFind;
    NDIlib_recv_instance_t ndiRecv;
};

struct NDI_t APV_Create_NDI();

const NDIlib_source_t* APV_Find_Sources(struct NDI_t ndi, uint32_t* no_sources);

#endif //NDI_H

/*********************
 *      INCLUDES
 *********************/
#ifndef __NFT_GALLERY_H__
#define __NFT_GALLERY_H__


#include "lvgl/lvgl.h"

typedef struct
{
	lv_obj_t* bg_cont;
} nft_gallery_t;


void nft_gallery_start(void);
void nft_gallery_stop(void);

#endif /* __NFT_GALLERY_H__ */


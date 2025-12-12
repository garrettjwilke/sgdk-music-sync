#include <genesis.h>
#include "../res/mdsdrv/mdsdrv.h"
#include "../res/mdsdrv/mdsseq.h"

u8 previous_comm_signal = 0;
void draw_comm_signals()
{
    // we can get comm signals from the MDS_command(16, 0)
    // it will return the number set in the MML 'comm' command
    u8 current_comm_signal = MDS_command(MDS_CMD_GET_COMM, 0);
    if (current_comm_signal == previous_comm_signal) {
        return;
    }
    int x = 16;
    int y = 11;
    VDP_clearTextArea(x, y, 7, 1);

    switch(current_comm_signal)
    {
        case 1: VDP_drawText("x      ", x, y); break;
        case 2: VDP_drawText("  x    ", x, y); break;
        case 3: VDP_drawText("    x  ", x, y); break;
        case 4: VDP_drawText("      x", x, y); break;
        default: break;
    }
}

int main() {
    // start MDSDRV init
    if(MDS_init(mdsseqdat, mdspcmdat))
	{
		VDP_drawText("MDSDRV init failed!!!!!", 2, 2);
		VDP_drawText("Please make sure that the driver and", 2, 4);
		VDP_drawText("sequence data version matches.", 2, 5);
		return 0;
	}
	SYS_setVIntCallback(vbl_callback);
    // end MDSDRV init

    MDS_request(MDS_BGM, BGM_HMLS_01); // play a song

    VDP_drawTextBG(BG_A, "MDSDRV - comm signals demo", 6, 2);
    VDP_drawTextBG(BG_A, "this is being read from the", 6, 4);
    VDP_drawTextBG(BG_A, "'comm' signals in the MML.", 6, 5);
    VDP_drawTextBG(BG_A, "1 2 3 4", 16, 10);

    VDP_drawTextBG(BG_A, "you can make game events", 6, 18);
    VDP_drawTextBG(BG_A, "that sync with your music!", 6, 19);

    while(1) {
        draw_comm_signals(); // read current comm signals and do stuffs in real time
        SYS_doVBlankProcess();
    }
    return 0;
}
// Roll a pair of 'dice'

PROGMEM const uint8_t dice[] = {
  0x00,0x00,0x00,
  0x00,0xFF,0x00,
  0x00,0x00,0x00,
  
  0x00,0x00,0x00,
  0xFF,0x00,0xFF,
  0x00,0x00,0x00,
  
  0x00,0x00,0x00,
  0xFC,0xFF,0xFF,
  0x00,0x00,0x00,
  
  0xFF,0x00,0xFF,
  0x00,0x00,0x00,
  0xFF,0x00,0xFF,
  
  0xFF,0x00,0xFF,
  0x00,0xFF,0x00,
  0xFF,0x00,0xFF,
  
  0xFF,0xFF,0xFF,
  0x00,0x00,0x00,
  0xFF,0xFF,0xFF };

// the dice roll iterates by number of frames
static uint8_t frames = 0xff, nframes = 0;
static uint8_t d1 = 0, d2 = 0;

void mode_dice(uint8_t action) {

  if(action != ACTION_NONE) {

    if(action >= ACTION_HOLD_LEFT) {
      uint8_t depth = 6, plex = LED_PLEX_4;
      // Reduce depth/plex if battery voltage is low
      if(watch.getmV() < BATT_LOW_MV) {
        depth = 2;
        plex  = LED_PLEX_1;
      }
      // Reconfigure display if needed
      if((watch.getDepth() != depth) || (watch.getPlex() != plex))
        fps = watch.setDisplayMode(depth, plex, true);
    }

    // interval between updates (no. of frames)
    nframes = 5;

    // Reset sleep timeout on ANY button action.
    watch.setTimeout(fps * 15);
  }

  // do a new roll every nframes; with increasing interval each roll
  if (nframes < 50) {  // stop rolling when we reach an interval of 50 frames
    if (frames > nframes) {
      frames = 0;
      nframes *= 1.2;
      d1 = random(6);
      d2 = random(6);
    }
  }
  frames++;

  watch.fillScreen(BACKGROUND);

  // blit the 3x3 glyph located at 'block' d1, to position 0,2 on the display
  blit(dice, 3, 3,     0, d1 * 3,    0, 2,   3, 3, 255);
  blit(dice, 3, 3,     0, d2 * 3,    5, 2,   3, 3, 255);

}


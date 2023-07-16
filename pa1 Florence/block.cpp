#include "block.h"
#include <cmath>
#include <iostream>

int Block::height() const {
  /* your code here */
  return data[0].size();
}

int Block::width() const {
  /* your code here */
  return data.size();
}

void Block::render(PNG &im, int x) const {

  /* your code here */
  for (int i = 0; i < width(); i++) {
    for (unsigned int j = 0; j < im.height(); j++) {
      *(im.getPixel(x + i, j)) = data[i][j];
    }
  }
}

  /** 
   * Creates a block that is width X img.height pixels in size
   * by copying the pixels from (x, 0) to (x+width-1, img.height-1)
   * in img. Assumes img is large enough to supply these pixels.
   */
void Block::build(PNG &im, int x, int width) {
  /* your code here */
  data.resize(width);

  for (int i = 0; i < width; i++) {
    data[i].resize(im.height());

    for (int j = 0; j < im.height(); j++) {
      data[i][j] = *(im.getPixel(x + i, j));
    }
  }
}


#ifndef NOISE_H
#define NOISE_H

// A bunch of functions to get deterministic random values

// Squirrel3 noise function, written by Squirrel Eiserloh

uint32_t noise(int position, uint32_t seed) {
  // Bunch of big prime numbers
  constexpr unsigned int bitNoise1 = 0xB5297A4D;
  constexpr unsigned int bitNoise2 = 0x68E31DA4;
  constexpr unsigned int bitNoise3 = 0x1B56C4E9;

  unsigned int mangled = position;
  mangled *= bitNoise1;
  mangled += seed;
  mangled ^= (mangled >> 8);
  mangled += bitNoise2;
  mangled ^= (mangled << 8);
  mangled *= bitNoise3;
  mangled ^= (mangled >> 8);
  return mangled;
}

inline uint32_t noise2d(int posX, int posY, uint32_t seed) {
  constexpr int primeNumber = 198491317;
  return noise(posX + (primeNumber * posY), seed);
}

inline uint32_t noise3d(int posX, int posY, int posZ, uint32_t seed) {
  constexpr int primeNumber = 198491317;
  constexpr int primeNumber2 = 6542989;
  return noise(posX + (primeNumber * posY) + (primeNumber2 * posZ), seed);
}

inline uint32_t noise4d(int posX, int posY, int posZ, int posW, uint32_t seed) {
  constexpr int primeNumber = 198491317;
  constexpr int primeNumber2 = 6542989;
  constexpr int primeNumber3 = 2415283853;
  return noise(posX + (primeNumber * posY) + (primeNumber2 * posZ) + (primeNumber3 * posW), seed);
}

inline double normalise(uint32_t input){
  constexpr uint32_t max=4294967295;
  double output=static_cast<double>(input);
  return output/=max;
}

#endif

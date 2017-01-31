//16 wide

int xMap[] = {
5,
5,
5,
4,
4,
4,
4,
4,
3,
3,
3,
3,
3,
2,
2,
2,
2,
2,
2,
2,
1,
1,
1,
1,
1,
1,

2,
2,
2,
2,
2,
3,
3,
3,
3,
3,
3,
4,
4,
4,
4,
4,
5,
5,
5,
5,
6,
6,
6,
6,
6,
7,
7,

8,
8,
8,
7,
7,
7,
7,
7,
6,
6,
6,
6,
6,
5,
5,
5,
5,
4,
4,
4,
4,
4,
4,
3,
3,
3,
3,

4,
4,
4,
4,
5,
5,
5,
5,
5,
6,
6,
6,
6,
6,
7,
7,
7,
7,
8,
8,
8,
8,
9,
9,
9,
9,
9,

11,
12,
12,
12,
12,
13,
13,
13,
13,
13,
13,
14,
14,
14,
14,
14,
15,
15,
15,
15,
15,
15,
16,
16,
16,
16,
16,

15,
15,
15,
14,
14,
14,
14,
14,
13,
13,
13,
13,
13,
13,
12,
12,
12,
12,
12,
11,
11,
11,
11,
11,
10,

10,
10,
10,
10,
10,
11,
11,
11,
11,
11,
12,
12,
12,
12,
12,
12,
13,
13,
13,
13,
13,
14,
15,

14,
13,
13,
13,
13,
13,
12,
12,
12,
12,
12,
11,
11,
11,
11,
11,
11,
10,
10,
10,

9,
9,
10,
10,
10,
10,
10,
11,
11,
11,
11,
11,
11,
12,
12,
12,
12,
12,

11,
11,
11,
11,
11,
10,
10,
10,
10,
10,
9,
9,
9,
9,
9,

8,
8,
8,
9,
9,
9,
9,
9,
10,
10,
10,
10,

9,
9,
9,
9,
8,
8,
8,
8,
7,
7,

7,
7,
7,
8,
8,
8,
8,

6,
6,
6,
6

};



int yMap[] = {

1,
2,
3,
4,
5,
6,
7,
8,
9,
10,
11,
12,
13,
14,
15,
16,
17,
18,
19,
20,
21,
22,
23,
24,
25,
26,

26,
26,
25,
24,
23,
22,
21,
20,
19,
18,
17,
16,
15,
14,
13,
12,
11,
10,
9,
8,
7,
6,
5,
4,
3,
2,
1, 

1,
2,
3,
4,
5,
6,
7,
8,
9,
10,
11,
12,
13,
14,
15,
16,
17,
18,
19,
20,
21,
22,
23,
24,
25,
26,
26,

26,
26,
25,
24,
23,
22,
21,
20,
19,
18,
17,
16,
15,
14,
13,
12,
11,
10,
9,
8,
7,
6,
5,
4,
3,
2,
1, 

1,
2,
3,
4,
5,
6,
7,
8,
9,
10,
11,
12,
13,
14,
15,
16,
17,
18,
19,
20,
21,
22,
23,
24,
25,
26,
26,

26,
26,
25,
24,
23,
22,
21,
20,
19,
18,
17,
16,
15,
14,
13,
12,
11,
10,
9,
8,
7,
6,
5,
4,
3,

5,
6,
7,
8,
9,
10,
11,
12,
13,
14,
15,
16,
17,
18,
19,
20,
21,
22,
23,
24,
25,
26,
26,

26,
26,
25,
24,
23,
22,
21,
20,
19,
18,
17,
16,
15,
14,
13,
12,
11,
10,
9,
8,

10,
11,
12,
13,
14,
15,
16,
17,
18,
19,
20,
21,
22,
23,
24,
25,
26,
26,

26,
26,
25,
24,
23,
22,
21,
20,
19,
18,
17,
16,
15,
14,
13,

16,
17,
18,
19,
20,
21,
22,
23,
24,
25,
26,
26,

26,
26,
25,
24,
23,
22,
21,
20,
19,
18,

21,
22,
23,
24,
25,
26,
26,

26,
26,
25,
24

};


int MAP_WIDTH = 16;
int MAP_HEIGHT = 26;

int forward(long frame, int i) {
  return i;
}

int peak(long frame, int i) {
  if (i < NUM_LEDS / 2) {
    return i;
  } else { 
    return NUM_LEDS - 1 - i;
  }
}

int valley(long frame, int i) {
  if (i < NUM_LEDS / 2) {
    return NUM_LEDS / 2 - 1 - i;
  } else { 
    return i;
  }
}

int dither(long frame, int i) {
  if (i % 2 == 0) {
    return NUM_LEDS - 1 - i;
  } else { 
    return i;
  }
}

int dekonstruktor(long frame, int i)
{
  if(frame%400 > 200)
  {
    return i + random(frame%200/4);
  }
  else
  {
    return i + random( (200-(frame%200) )/4);
  } 
}



int H_forward(long frame, int i) {
  return xMap[i];
}

int H_peak(long frame, int i) {
  i = xMap[i] - 1;
  if (i < MAP_WIDTH / 2) {
    return i;
  } else { 
    return MAP_WIDTH - 1 - i;
  }
}

int H_valley(long frame, int i) {
  i = xMap[i] - 1;
  if (i < MAP_WIDTH / 2) {
    return MAP_WIDTH / 2 - 1 - i;
  } else { 
    return i;
  }
}

int H_dither(long frame, int i) {
  i = xMap[i] - 1;
  if (i % 2 == 0) {
    return MAP_WIDTH - 1 - i;
  } else { 
    return i;
  }
}

int H_dekonstruktor(long frame, int i)
{
  i = xMap[i] - 1;
  if(frame%400 > 200)
  {
    return i + random(frame%200/4);
  }
  else
  {
    return i + random( (200-(frame%200) )/4);
  } 
}




int V_forward(long frame, int i) {
  return yMap[i];
}

int V_peak(long frame, int i) {
  i = yMap[i] - 1;
  if (i < MAP_HEIGHT / 2) {
    return i;
  } else { 
    return MAP_HEIGHT - 1 - i;
  }
}

int V_valley(long frame, int i) {
  i = yMap[i] - 1;
  if (i < MAP_HEIGHT / 2) {
    return MAP_HEIGHT / 2 - 1 - i;
  } else { 
    return i;
  }
}

int V_dither(long frame, int i) {
  i = yMap[i] - 1;
  if (i % 2 == 0) {
    return MAP_HEIGHT - 1 - i;
  } else { 
    return i;
  }
}

int V_dekonstruktor(long frame, int i)
{
  i = yMap[i] - 1;
  if(frame%400 > 200)
  {
    return i + random(frame%200/4);
  }
  else
  {
    return i + random( (200-(frame%200) )/4);
  } 
}




int pxToVertical(long frame, int i){
  return yMap[i];
}

int pxToHorizontal(long frame, int i){
  // int index = 0;
  // for(int k = 0; k < sizeof(xMap); k++){

  //   if(i < index + xMap[k]  && i > index - 1){
  //     return k;
  //   }
  //   index+=xMap[k];
  // }

  return xMap[i];
}



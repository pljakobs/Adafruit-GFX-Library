/*
 * collection of 141 html defined colors to be referenced by name.
 * to directly use them in a draw routine, use something like
 * display.drawPixel(x,y,LIGHTCORAL);
 * to use it on an interleaved bitmap canvas, you have to add it to a
 * pallette position first.
 * in Order to do that you need to call
 * canvas.setColor(index,colorname);
 * for example:
 * canvas.setColor(7,CRIMSON);
 * after that, you can call
 * canvas.drawPixel(x,y,7);
 * to draw a crimson colored pixel.
 */
 
#define INDIANRED       {205, 92, 92}
#define LIGHTCORAL      {240, 128, 128}
#define SALMON          {250, 128, 114}
#define DARKSALMON      {233, 150, 122}
#define LIGHTSALMON     {255, 160, 122}
#define CRIMSON         {220, 20, 60}
#define RED             {255, 0, 0}
#define FIREBRICK       {178, 34, 34}
#define DARKRED         {139, 0, 0}
#define PINK            {255, 192, 203}
#define LIGHTPINK       {255, 182, 193}
#define HOTPINK         {255, 105, 180}
#define DEEPPINK        {255, 20, 147}
#define MEDIUMVIOLETRED {199, 21, 133}
#define PALEVIOLETRED   {219, 112, 147}
#define CORAL           {255, 127, 80}
#define TOMATO          {255, 99, 71}
#define ORANGERED       {255, 69, 0}
#define DARKORANGE      {255, 140, 0}
#define ORANGE          {255, 165, 0}
#define GOLD            {255, 215, 0}
#define YELLOW          {255, 255, 0}
#define LIGHTYELLOW     {255, 255, 224}
#define LEMONCHIFFON    {255, 250, 205}
#define LIGHTGOLDENRODYELLOW {250, 250, 210}
#define PAPAYAWHIP      {255, 239, 213}
#define MOCCASIN        {255, 228, 181}
#define PEACHPUFF       {255, 218, 185}
#define PALEGOLDENROD   {238, 232, 170}
#define KHAKI           {240, 230, 140}
#define DARKKHAKI       {189, 183, 107}
#define LAVENDER        {230, 230, 250}
#define THISTLE         {216, 191, 216}
#define PLUM            {221, 160, 221}
#define VIOLET          {238, 130, 238}
#define ORCHID          {218, 112, 214}
#define FUCHSIA         {255, 0, 255}
#define MAGENTA         {255, 0, 255}
#define MEDIUMORCHID    {186, 85, 211}
#define MEDIUMPURPLE    {147, 112, 219}
#define REBECCAPURPLE   {102, 51, 153}
#define BLUEVIOLET      {138, 43, 226}
#define DARKVIOLET      {148, 0, 211}
#define DARKORCHID      {153, 50, 204}
#define DARKMAGENTA     {139, 0, 139}
#define PURPLE          {128, 0, 128}
#define INDIGO          {75, 0, 130}
#define SLATEBLUE       {106, 90, 205}
#define DARKSLATEBLUE   {72, 61, 139}
#define MEDIUMSLATEBLUE {123, 104, 238}
#define GREENYELLOW     {173, 255, 47}
#define CHARTREUSE      {127, 255, 0}
#define LAWNGREEN       {124, 252, 0}
#define LIME            {0, 255, 0}
#define LIMEGREEN       {50, 205, 50}
#define PALEGREEN       {152, 251, 152}
#define LIGHTGREEN      {144, 238, 144}
#define MEDIUMSPRINGGREEN {0, 250, 154}
#define SPRINGGREEN     {0, 255, 127}
#define MEDIUMSEAGREEN  {60, 179, 113}
#define SEAGREEN        {46, 139, 87}
#define FORESTGREEN     {34, 139, 34}
#define GREEN           {0, 128, 0}
#define DARKGREEN       {0, 100, 0}
#define YELLOWGREEN     {154, 205, 50}
#define OLIVEDRAB       {107, 142, 35}
#define OLIVE           {128, 128, 0}
#define DARKOLIVEGREEN  {85, 107, 47}
#define MEDIUMAQUAMARINE {102, 205, 170}
#define DARKSEAGREEN    {143, 188, 139}
#define LIGHTSEAGREEN   {32, 178, 170}
#define DARKCYAN        {0, 139, 139}
#define TEAL            {0, 128, 128}
#define AQUA            {0, 255, 255}
#define CYAN            {0, 255, 255}
#define LIGHTCYAN       {224, 255, 255}
#define PALETURQUOISE   {175, 238, 238}
#define AQUAMARINE      {127, 255, 212}
#define TURQUOISE       {64, 224, 208}
#define MEDIUMTURQUOISE {72, 209, 204}
#define DARKTURQUOISE   {0, 206, 209}
#define CADETBLUE       {95, 158, 160}
#define STEELBLUE       {70, 130, 180}
#define LIGHTSTEELBLUE  {176, 196, 222}
#define POWDERBLUE      {176, 224, 230}
#define LIGHTBLUE       {173, 216, 230}
#define SKYBLUE         {135, 206, 235}
#define LIGHTSKYBLUE    {135, 206, 250}
#define DEEPSKYBLUE     {0, 191, 255}
#define DODGERBLUE      {30, 144, 255}
#define CORNFLOWERBLUE  {100, 149, 237}
#define ROYALBLUE       {65, 105, 225}
#define BLUE            {0, 0, 255}
#define MEDIUMBLUE      {0, 0, 205}
#define DARKBLUE        {0, 0, 139}
#define NAVY            {0, 0, 128}
#define MIDNIGHTBLUE    {25, 25, 112}
#define CORNSILK        {255, 248, 220}
#define BLANCHEDALMOND  {255, 235, 205}
#define BISQUE          {255, 228, 196}
#define NAVAJOWHITE     {255, 222, 173}
#define WHEAT           {245, 222, 179}
#define BURLYWOOD       {222, 184, 135}
#define TAN             {210, 180, 140}
#define ROSYBROWN       {188, 143, 143}
#define SANDYBROWN      {244, 164, 96}
#define GOLDENROD       {218, 165, 32}
#define DARKGOLDENROD   {184, 134, 11}
#define PERU            {205, 133, 63}
#define CHOCOLATE       {210, 105, 30}
#define SADDLEBROWN     {139, 69, 19}
#define SIENNA          {160, 82, 45}
#define BROWN           {165, 42, 42}
#define MAROON          {128, 0, 0}
#define WHITE           {255, 255, 255}
#define SNOW            {255, 250, 250}
#define HONEYDEW        {240, 255, 240}
#define MINTCREAM       {245, 255, 250}
#define AZURE           {240, 255, 255}
#define ALICEBLUE       {240, 248, 255}
#define GHOSTWHITE      {248, 248, 255}
#define WHITESMOKE      {245, 245, 245}
#define SEASHELL        {255, 245, 238}
#define BEIGE           {245, 245, 220}
#define OLDLACE         {253, 245, 230}
#define FLORALWHITE     {255, 250, 240}
#define IVORY           {255, 255, 240}
#define ANTIQUEWHITE    {250, 235, 215}
#define LINEN           {250, 240, 230}
#define LAVENDERBLUSH   {255, 240, 245}
#define MISTYROSE       {255, 228, 225}
#define GAINSBORO       {220, 220, 220}
#define LIGHTGRAY       {211, 211, 211}
#define SILVER          {192, 192, 192}
#define DARKGRAY        {169, 169, 169}
#define GRAY            {128, 128, 128}
#define DIMGRAY         {105, 105, 105}
#define LIGHTSLATEGRAY  {119, 136, 153}
#define SLATEGRAY       {112, 128, 144}
#define DARKSLATEGRAY   {47, 79, 79}
#define BLACK           {0, 0, 0}

/*
#define PAL_INDIANRED	  1
#define PAL_LIGHTCORAL	2
#define PAL_SALMON	    3
#define PAL_DARKSALMON	4
#define PAL_LIGHTSALMON	5
#define PAL_CRIMSON	    6
#define PAL_RED	        7
#define PAL_FIREBRICK	  8
#define PAL_DARKRED	    9
#define PAL_PINK	      10
#define PAL_LIGHTPINK	  11
#define PAL_HOTPINK	    12
#define PAL_DEEPPINK	  13
#define PAL_MEDIUMVIOLETRED	14
#define PAL_PALEVIOLETRED	15
#define PAL_CORAL	      16
#define PAL_TOMATO	    17
#define PAL_ORANGERED	  18
#define PAL_DARKORANGE	10
#define PAL_ORANGE	    20
#define PAL_GOLD	      21
#define PAL_YELLOW	    22
#define PAL_LIGHTYELLOW	23
#define PAL_LEMONCHIFFON	24
#define PAL_LIGHTGOLDENRODYELLOW	25
#define PAL_PAPAYAWHIP	26
#define PAL_MOCCASIN	  27
#define PAL_PEACHPUFF	  28
#define PAL_PALEGOLDENROD	29
#define PAL_KHAKI	      30
#define PAL_DARKKHAKI	  31
#define PAL_LAVENDER	  32
#define PAL_THISTLE	    33
#define PAL_PLUM	      34
#define PAL_VIOLET	    35
#define PAL_ORCHID	    36
#define PAL_FUCHSIA	    37
#define PAL_MAGENTA	    38
#define PAL_MEDIUMORCHID	39
#define PAL_MEDIUMPURPLE	40
#define PAL_REBECCAPURPLE	41
#define PAL_BLUEVIOLET	42
#define PAL_DARKVIOLET	43
#define PAL_DARKORCHID	44
#define PAL_DARKMAGENTA	45
#define PAL_PURPLE	46
#define PAL_INDIGO	47
#define PAL_SLATEBLUE	48
#define PAL_DARKSLATEBLUE	49
#define PAL_MEDIUMSLATEBLUE	50
#define PAL_GREENYELLOW	51
#define PAL_CHARTREUSE	52
#define PAL_LAWNGREEN	53
#define PAL_LIME	54
#define PAL_LIMEGREEN	55
#define PAL_PALEGREEN	56
#define PAL_LIGHTGREEN	57
#define PAL_MEDIUMSPRINGGREEN	58
#define PAL_SPRINGGREEN	59
#define PAL_MEDIUMSEAGREEN	60
#define PAL_SEAGREEN	61
#define PAL_FORESTGREEN	62
#define PAL_GREEN	63
#define PAL_DARKGREEN	64
#define PAL_YELLOWGREEN 65
#define PAL_OLIVEDRAB	66
#define PAL_OLIVE	67
#define PAL_DARKOLIVEGREEN	68
#define PAL_MEDIUMAQUAMARINE	69
#define PAL_DARKSEAGREEN	70
#define PAL_LIGHTSEAGREEN	71
#define PAL_DARKCYAN	72
#define PAL_TEAL	73
#define PAL_AQUA	74
#define PAL_CYAN	75
#define PAL_LIGHTCYAN	76
#define PAL_PALETURQUOISE	77
#define PAL_AQUAMARINE	78
#define PAL_TURQUOISE	79
#define PAL_MEDIUMTURQUOISE	80
#define PAL_DARKTURQUOISE	81
#define PAL_CADETBLUE	82
#define PAL_STEELBLUE	83
#define PAL_LIGHTSTEELBLUE	84
#define PAL_POWDERBLUE	85
#define PAL_LIGHTBLUE	86
#define PAL_SKYBLUE	87
#define PAL_LIGHTSKYBLUE	88
#define PAL_DEEPSKYBLUE	89
#define PAL_DODGERBLUE	90
#define PAL_CORNFLOWERBLUE	91
#define PAL_ROYALBLUE	92
#define PAL_BLUE	93
#define PAL_MEDIUMBLUE	94
#define PAL_DARKBLUE	95
#define PAL_NAVY	96
#define PAL_MIDNIGHTBLUE	97
#define PAL_CORNSILK	98
#define PAL_BLANCHEDALMOND	99
#define PAL_BISQUE	100
#define PAL_NAVAJOWHITE	101
#define PAL_WHEAT	102
#define PAL_BURLYWOOD	103
#define PAL_TAN	104
#define PAL_ROSYBROWN	105
#define PAL_SANDYBROWN	106
#define PAL_GOLDENROD	107
#define PAL_DARKGOLDENROD	108
#define PAL_PERU	109
#define PAL_CHOCOLATE	110
#define PAL_SADDLEBROWN	111
#define PAL_SIENNA	112
#define PAL_BROWN	113
#define PAL_MAROON	114
#define PAL_WHITE	115
#define PAL_SNOW	116
#define PAL_HONEYDEW	117
#define PAL_MINTCREAM	118
#define PAL_AZURE	119
#define PAL_ALICEBLUE	120
#define PAL_GHOSTWHITE	121
#define PAL_WHITESMOKE	122
#define PAL_SEASHELL	123
#define PAL_BEIGE	124
#define PAL_OLDLACE	125
#define PAL_FLORALWHITE	126
#define PAL_IVORY	127
#define PAL_ANTIQUEWHITE	128
#define PAL_LINEN	129
#define PAL_LAVENDERBLUSH	130
#define PAL_MISTYROSE	131
#define PAL_GAINSBORO	132
#define PAL_LIGHTGRAY	133
#define PAL_SILVER	134
#define PAL_DARKGRAY	135
#define PAL_GRAY	136
#define PAL_DIMGRAY	137
#define PAL_LIGHTSLATEGRAY	138
#define PAL_SLATEGRAY	139
#define PAL_DARKSLATEGRAY	140
#define PAL_BLACK 141
*/

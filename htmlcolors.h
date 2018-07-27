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

#define html_BLACK        0
#define BLACK             {0, 0, 0}

#define html_WHITE	      1
#define WHITE             {255, 255, 255}

#define html_INDIANRED    2
#define INDIANRED         {205, 92, 92}

#define html_LIGHTCORAL	  3
#define LIGHTCORAL        {240, 128, 128}

#define html_SALMON	      4
#define SALMON            {250, 128, 114}

#define html_DARKSALMON	  5
#define DARKSALMON        {233, 150, 122}

#define html_LIGHTSALMON	6
#define LIGHTSALMON       {255, 160, 122}

#define html_CRIMSON	    7
#define CRIMSON           {220, 20, 60}

#define html_RED	        8
#define RED               {255, 0, 0}

#define html_FIREBRICK	  9
#define FIREBRICK         {178, 34, 34}

#define html_DARKRED	    10
#define DARKRED           {139, 0, 0}

#define html_PINK	        11
#define PINK              {255, 192, 203}

#define html_LIGHTPINK	  12
#define LIGHTPINK         {255, 182, 193}

#define html_HOTPINK	    13
#define HOTPINK           {255, 105, 180}

#define html_DEEPPINK	    14
#define DEEPPINK          {255, 20, 147}

#define html_MEDIUMVIOLETRED	15
#define MEDIUMVIOLETRED       {199, 21, 133}

#define html_PALEVIOLETRED 16
#define PALEVIOLETRED      {219, 112, 147}

#define html_CORAL	       17
#define CORAL              {255, 127, 80}

#define html_TOMATO	       18
#define TOMATO             {255, 99, 71}

#define html_ORANGERED	   19
#define ORANGERED          {255, 69, 0}

#define html_DARKORANGE	   20
#define DARKORANGE         {255, 140, 0}

#define html_ORANGE	       21
#define ORANGE             {255, 165, 0}

#define html_GOLD	         22
#define GOLD               {255, 215, 0}

#define html_YELLOW	       23
#define YELLOW             {255, 255, 0}

#define html_LIGHTYELLOW	 24
#define LIGHTYELLOW        {255, 255, 224}

#define html_LEMONCHIFFON	 25
#define LEMONCHIFFON       {255, 250, 205}

#define html_LIGHTGOLDENRODYELLOW	26
#define LIGHTGOLDENRODYELLOW      {250, 250, 210}

#define html_PAPAYAWHIP	   27
#define PAPAYAWHIP         {255, 239, 213}

#define html_MOCCASIN	     28
#define MOCCASIN           {255, 228, 181}

#define html_PEACHPUFF	   29
#define PEACHPUFF          {255, 218, 185}

#define html_PALEGOLDENROD 30
#define PALEGOLDENROD      {238, 232, 170}

#define html_KHAKI	       31
#define KHAKI              {240, 230, 140}

#define html_DARKKHAKI	   32
#define DARKKHAKI          {189, 183, 107}

#define html_LAVENDER	     33
#define LAVENDER           {230, 230, 250}

#define html_THISTLE	     34
#define THISTLE            {216, 191, 216}

#define html_PLUM	         35
#define PLUM               {221, 160, 221}

#define html_VIOLET	       36
#define VIOLET             {238, 130, 238}

#define html_ORCHID	       37
#define ORCHID             {218, 112, 214}

#define html_FUCHSIA	     38
#define FUCHSIA            {255, 0, 255}

#define html_MAGENTA	     39
#define MAGENTA            {255, 0, 255}

#define html_MEDIUMORCHID	 40
#define MEDIUMORCHID       {186, 85, 211}

#define html_MEDIUMPURPLE	 41
#define MEDIUMPURPLE       {147, 112, 219}

#define html_REBECCAPURPLE  42
#define REBECCAPURPLE       {102, 51, 153}

#define html_BLUEVIOLET	    43
#define BLUEVIOLET          {138, 43, 226}

#define html_DARKVIOLET	    44
#define DARKVIOLET          {148, 0, 211}

#define html_DARKORCHID	    45
#define DARKORCHID          {153, 50, 204}

#define html_DARKMAGENTA	  46
#define DARKMAGENTA         {139, 0, 139}

#define html_PURPLE	        47
#define PURPLE              {128, 0, 128}

#define html_INDIGO	        48
#define INDIGO              {75, 0, 130}

#define html_SLATEBLUE	    49
#define SLATEBLUE           {106, 90, 205}

#define html_DARKSLATEBLUE	50
#define DARKSLATEBLUE       {72, 61, 139}

#define html_MEDIUMSLATEBLUE 51
#define MEDIUMSLATEBLUE      {123, 104, 238}

#define html_GREENYELLOW	  52
#define GREENYELLOW         {173, 255, 47}

#define html_CHARTREUSE	    53
#define CHARTREUSE          {127, 255, 0}

#define html_LAWNGREEN	    54
#define LAWNGREEN           {124, 252, 0}

#define html_LIME	          55
#define LIME                {0, 255, 0}

#define html_LIMEGREEN	    56
#define LIMEGREEN           {50, 205, 50}

#define html_PALEGREEN	    57
#define PALEGREEN           {152, 251, 152}

#define html_LIGHTGREEN	    58
#define LIGHTGREEN          {144, 238, 144}

#define html_MEDIUMSPRINGGREEN 59
#define MEDIUMSPRINGGREEN      {0, 250, 154}

#define html_SPRINGGREEN	  60
#define SPRINGGREEN         {0, 255, 127}

#define html_MEDIUMSEAGREEN	61
#define MEDIUMSEAGREEN      {60, 179, 113}

#define html_SEAGREEN	      62
#define SEAGREEN            {46, 139, 87}

#define html_FORESTGREEN	  63
#define FORESTGREEN         {34, 139, 34}

#define html_GREEN	        64
#define GREEN               {0, 128, 0}

#define html_DARKGREEN	    65
#define DARKGREEN           {0, 100, 0}

#define html_YELLOWGREEN    66
#define YELLOWGREEN         {154, 205, 50}

#define html_OLIVEDRAB	    67
#define OLIVEDRAB           {107, 142, 35}

#define html_OLIVE	        68
#define OLIVE               {128, 128, 0}

#define html_DARKOLIVEGREEN	69
#define DARKOLIVEGREEN      {85, 107, 47}

#define html_MEDIUMAQUAMARINE	70
#define MEDIUMAQUAMARINE      {102, 205, 170}

#define html_DARKSEAGREEN	  71
#define DARKSEAGREEN        {143, 188, 139}

#define html_LIGHTSEAGREEN	72
#define LIGHTSEAGREEN       {32, 178, 170}

#define html_DARKCYAN	      73
#define DARKCYAN            {0, 139, 139}

#define html_TEAL	          74
#define TEAL                {0, 128, 128}

#define html_AQUA	          75
#define AQUA                {0, 255, 255}

#define html_CYAN	          76
#define CYAN                {0, 255, 255}

#define html_LIGHTCYAN	    77
#define LIGHTCYAN           {224, 255, 255}

#define html_PALETURQUOISE	78
#define PALETURQUOISE       {175, 238, 238}

#define html_AQUAMARINE	    79
#define AQUAMARINE          {127, 255, 212}

#define html_TURQUOISE	    80
#define TURQUOISE           {64, 224, 208}

#define html_MEDIUMTURQUOISE 81
#define MEDIUMTURQUOISE      {72, 209, 204}

#define html_DARKTURQUOISE 82
#define DARKTURQUOISE      {0, 206, 209}

#define html_CADETBLUE	   83
#define CADETBLUE          {95, 158, 160}

#define html_STEELBLUE	   84
#define STEELBLUE          {70, 130, 180}

#define html_LIGHTSTEELBLUE	85
#define LIGHTSTEELBLUE      {176, 196, 222}

#define html_POWDERBLUE	  86
#define POWDERBLUE        {176, 224, 230}

#define html_LIGHTBLUE	  87
#define LIGHTBLUE         {173, 216, 230}

#define html_SKYBLUE	    88
#define SKYBLUE           {135, 206, 235}

#define html_LIGHTSKYBLUE	89
#define LIGHTSKYBLUE      {135, 206, 250}

#define html_DEEPSKYBLUE	90
#define DEEPSKYBLUE       {0, 191, 255}

#define html_DODGERBLUE	  91
#define DODGERBLUE        {30, 144, 255}

#define html_CORNFLOWERBLUE	92
#define CORNFLOWERBLUE      {100, 149, 237}

#define html_ROYALBLUE	  93
#define ROYALBLUE         {65, 105, 225}

#define html_BLUE	      94
#define BLUE            {0, 0, 255}

#define html_MEDIUMBLUE	95
#define MEDIUMBLUE      {0, 0, 205}

#define html_DARKBLUE	    96
#define DARKBLUE        {0, 0, 139}

#define html_NAVY	        97
#define NAVY            {0, 0, 128}

#define html_MIDNIGHTBLUE	98
#define MIDNIGHTBLUE    {25, 25, 112}

#define html_CORNSILK	    99
#define CORNSILK        {255, 248, 220}

#define html_BLANCHEDALMOND	100
#define BLANCHEDALMOND  {255, 235, 205}

#define html_BISQUE	     101
#define BISQUE          {255, 228, 196}

#define html_NAVAJOWHITE 102
#define NAVAJOWHITE     {255, 222, 173}

#define html_WHEAT	     103
#define WHEAT           {245, 222, 179}

#define html_BURLYWOOD	 104
#define BURLYWOOD       {222, 184, 135}

#define html_TAN	105
#define TAN             {210, 180, 140}

#define html_ROSYBROWN	 106
#define ROSYBROWN       {188, 143, 143}

#define html_SANDYBROWN	 107
#define SANDYBROWN      {244, 164, 96}

#define html_GOLDENROD	 108
#define GOLDENROD       {218, 165, 32}

#define html_DARKGOLDENROD	109
#define DARKGOLDENROD   {184, 134, 11}

#define html_PERU	       110
#define PERU            {205, 133, 63}

#define html_CHOCOLATE	 111
#define CHOCOLATE       {210, 105, 30}

#define html_SADDLEBROWN 112
#define SADDLEBROWN     {139, 69, 19}

#define html_SIENNA	     113
#define SIENNA          {160, 82, 45}

#define html_BROWN	     114
#define BROWN           {165, 42, 42}

#define html_MAROON	     115
#define MAROON          {128, 0, 0}

#define html_SNOW	       116
#define SNOW            {255, 250, 250}

#define html_HONEYDEW	   117
#define HONEYDEW        {240, 255, 240}

#define html_MINTCREAM	 118
#define MINTCREAM       {245, 255, 250}

#define html_AZURE	     119
#define AZURE           {240, 255, 255}

#define html_ALICEBLUE	 120
#define ALICEBLUE       {240, 248, 255}

#define html_GHOSTWHITE	 121
#define GHOSTWHITE      {248, 248, 255}

#define html_WHITESMOKE	 122
#define WHITESMOKE      {245, 245, 245}

#define html_SEASHELL	   123
#define SEASHELL        {255, 245, 238}

#define html_BEIGE	     124
#define BEIGE           {245, 245, 220}

#define html_OLDLACE	   125
#define OLDLACE         {253, 245, 230}

#define html_FLORALWHITE 126
#define FLORALWHITE     {255, 250, 240}

#define html_IVORY      127
#define IVORY           {255, 255, 240}

#define html_ANTIQUEWHITE	128
#define ANTIQUEWHITE    {250, 235, 215}

#define html_LINEN	     129
#define LINEN           {250, 240, 230}

#define html_LAVENDERBLUSH	130
#define LAVENDERBLUSH   {255, 240, 245}

#define html_MISTYROSE	 131
#define MISTYROSE       {255, 228, 225}

#define html_GAINSBORO	 132
#define GAINSBORO       {220, 220, 220}

#define html_LIGHTGRAY	 133
#define LIGHTGRAY       {211, 211, 211}

#define html_SILVER	     134
#define SILVER          {192, 192, 192}

#define html_DARKGRAY  	 135
#define DARKGRAY        {169, 169, 169}

#define html_GRAY	       136
#define GRAY            {128, 128, 128}

#define html_DIMGRAY	   137
#define DIMGRAY         {105, 105, 105}

#define html_LIGHTSLATEGRAY	138
#define LIGHTSLATEGRAY  {119, 136, 153}

#define html_SLATEGRAY	 139
#define SLATEGRAY       {112, 128, 144}

#define html_DARKSLATEGRAY	140
#define DARKSLATEGRAY   {47, 79, 79}

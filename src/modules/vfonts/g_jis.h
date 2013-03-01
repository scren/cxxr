/*CXXR $Id$
 *CXXR
 *CXXR This file is part of CXXR, a project to refactor the R interpreter
 *CXXR into C++.  It may consist in whole or in part of program code and
 *CXXR documentation taken from the R project itself, incorporated into
 *CXXR CXXR (and possibly MODIFIED) under the terms of the GNU General Public
 *CXXR Licence.
 *CXXR 
 *CXXR CXXR is Copyright (C) 2008-13 Andrew R. Runnalls, subject to such other
 *CXXR copyrights and copyright restrictions as may be stated below.
 *CXXR 
 *CXXR CXXR is not part of the R project, and bugs and other issues should
 *CXXR not be reported via r-bugs or other R project channels; instead refer
 *CXXR to the CXXR website.
 *CXXR */

/* This header file is #include'd by g_cntrlify.c.  It is a database rather
   than a true header file: it includes information on characters in the
   JIS X 0208 two-byte encoding (containing Kanji, Kana, Roman letters,
   Greek letters, Cyrillic letters, etc). */

/* Whether a JIS index (two bytes) defines a JIS character, irrespective of
   whether we have a glyph for it.  (If it isn't a character, it ideally
   prints as a zero-width glyph; if it's a character but we don't have it,
   it ideally prints as an empty glyph or an `undefined' glyph.) */

#define GOOD_JIS_INDEX(row, col) \
	((row) > 0x20 && (row) < 0x7f && (col) > 0x20 && (col) < 0x7f)

#define BEGINNING_OF_KANJI 0x3000 /* Kanji afterwards, non-Kanji before */

#ifndef RAW_HERSHEY_GLYPH
#define RAW_HERSHEY_GLYPH 0x4000
#endif

struct kanjipair
{
  int jis, nelson;
};

/* The 603 Kanji that we have glyphs for.  1st field is JIS index number;
   2nd is Nelson index number, which we use internally (it indexes into the
   Hershey oriental glyph array in g_her_glyph.c).  For info on
   correspondence, see kanji.doc. */

static const struct kanjipair _builtin_kanji_glyphs[] =
{
  /* 596 Level 1 Kanji */
  /* row 16 */
  {0x3021, 43},
  {0x3026, 2829},
  {0x302d, 62},
  {0x3035, 818},
  {0x303f, 1802},
  {0x3045, 2154},
  {0x304c, 401},
  {0x3057, 2107},
  {0x3059, 138},
  {0x305b, 3008},
  {0x305e, 3579},
  {0x3061, 4214},
  {0x306c, 1},
  {0x3070, 3294},
  {0x3078, 1026},
  {0x307a, 1562},
  /* row 17 */
  {0x3122, 5006},
  {0x3126, 878},
  {0x3127, 1280},
  {0x3129, 3673},
  {0x312b, 5042},
  {0x3132, 2629},
  {0x313b, 2973},
  {0x313f, 4725},
  {0x3140, 5046},
  {0x314a, 130},
  {0x3155, 2599},
  {0x315f, 617},
  {0x3173, 4733},
  {0x3176, 1125},
  {0x3177, 2083},
  {0x317e, 1504},
  /* row 18 */
  {0x3221, 1885},
  {0x3223, 2361},
  {0x3226, 2922},
  {0x322b, 5399},
  {0x322f, 551},
  {0x3235, 260},
  {0x3239, 2634},
  {0x323b, 5110},
  {0x323c, 9},
  {0x323d, 350},
  {0x323f, 409},
  {0x3241, 422},
  {0x3243, 716},
  {0x3244, 24},
  {0x3246, 58},
  {0x3248, 1311},
  {0x324a, 3272},
  {0x324c, 107},
  {0x324f, 2530},
  {0x3250, 2743},
  {0x3256, 3909},
  {0x3259, 3956},
  {0x3261, 4723},
  {0x3267, 2848},
  {0x3268, 50},
  {0x3272, 4306},
  {0x3273, 1028},
  /* row 19 */
  {0x3323, 2264},
  {0x3324, 2553},
  {0x3326, 2998},
  {0x3328, 3537},
  {0x332b, 4950},
  {0x332d, 4486},
  {0x3330, 1168},
  {0x3346, 1163},
  {0x334b, 2254},
  {0x3351, 4301},
  {0x3353, 4623},
  {0x3357, 5088},
  {0x3358, 1271},
  {0x335a, 2324},
  {0x3364, 703},
  /* row 20 */
  {0x3424, 2977},
  {0x3428, 1322},
  {0x342c, 1466},
  {0x3433, 1492},
  {0x3434, 790},
  {0x3436, 1731},
  {0x3437, 1756},
  {0x3445, 2988},
  {0x3449, 3416},
  {0x3454, 4750},
  {0x3456, 4949},
  {0x3458, 4958},
  {0x346f, 994},
  {0x3470, 1098},
  {0x3476, 1496},
  {0x347c, 3785},
  /* row 21 */
  {0x3521, 2379},
  {0x3522, 1582},
  {0x3524, 2480},
  {0x3525, 2507},
  {0x352d, 4318},
  {0x3530, 4610},
  {0x3534, 5276},
  {0x3535, 5445},
  {0x3546, 3981},
  {0x3555, 4685},
  {0x355a, 154},
  {0x355b, 885},
  {0x355d, 1560},
  {0x3565, 2941},
  {0x3566, 3314},
  {0x3569, 3496},
  {0x356d, 2852},
  {0x356e, 1051},
  {0x356f, 1387},
  {0x3575, 4109},
  {0x3577, 4548},
  {0x357b, 5281},
  {0x357e, 295},
  /* row 22 */
  {0x3621, 431},
  {0x3626, 581},
  {0x362d, 1135},
  {0x362f, 1571},
  {0x3635, 2052},
  {0x3636, 2378},
  {0x364a, 103},
  {0x364b, 2305},
  {0x364c, 2923},
  {0x3651, 1065},
  {0x3661, 4671},
  {0x3662, 4815},
  {0x3664, 4855},
  {0x3665, 146},
  {0x3671, 3128},
  {0x3675, 3317},
  {0x367e, 1386},
  /* row 23 */
  {0x3738, 449},
  {0x3739, 534},
  {0x373e, 2937},
  {0x373f, 1077},
  {0x3741, 1589},
  {0x3742, 1602},
  {0x374f, 195},
  {0x3750, 3523},
  {0x3757, 4312},
  {0x375a, 4620},
  {0x3767, 2412},
  {0x3768, 2509},
  {0x376a, 3313},
  {0x376b, 3540},
  {0x376c, 4205},
  {0x376e, 2169},
  {0x3777, 1045},
  /* row 24 */
  {0x3824, 2868},
  {0x3826, 3180},
  {0x3828, 3543},
  {0x382b, 4284},
  {0x3833, 5220},
  {0x3835, 275},
  {0x3836, 825},
  {0x3839, 1568},
  {0x383a, 2637},
  {0x383b, 2656},
  {0x383d, 2943},
  {0x3840, 4309},
  {0x3842, 4987},
  {0x3845, 770},
  {0x3847, 1036},
  {0x384c, 1567},
  {0x384d, 1817},
  {0x384e, 2044},
  {0x385d, 5415},
  {0x385e, 15},
  {0x3861, 162},
  {0x3865, 1610},
  {0x3866, 1628},
  {0x386c, 4374},
  {0x3872, 290},
  {0x3877, 1358},
  {0x3878, 579},
  {0x387d, 868},
  {0x387e, 101},
  /* row 25 */
  {0x3929, 1451},
  {0x3931, 1683},
  {0x393d, 2343},
  {0x3943, 92},
  {0x394d, 3684},
  {0x3954, 4213},
  {0x3955, 1641},
  {0x395b, 4843},
  {0x395d, 4883},
  {0x395f, 4994},
  {0x3960, 1459},
  {0x3961, 5188},
  {0x3962, 5248},
  {0x3966, 882},
  {0x3967, 383},
  {0x3971, 1037},
  {0x3975, 5403},
  {0x397c, 5236},
  {0x397e, 4660},
  /* row 26 */
  {0x3a21, 2430},
  {0x3a23, 352},
  {0x3a2c, 2261},
  {0x3a38, 1455},
  {0x3a39, 3662},
  {0x3a42, 1515},
  {0x3a46, 35},
  {0x3a47, 2146},
  {0x3a59, 3522},
  {0x3a5f, 1055},
  {0x3a6e, 407},
  {0x3a72, 2119},
  {0x3a79, 2256},
  /* row 27 */
  {0x3b2e, 3113},
  {0x3b30, 8},
  {0x3b33, 1407},
  {0x3b36, 2056},
  {0x3b3b, 3415},
  {0x3b40, 4789},
  {0x3b45, 362},
  {0x3b4d, 1025},
  {0x3b4e, 1160},
  {0x3b4f, 1208},
  {0x3b52, 1264},
  {0x3b54, 284},
  {0x3b57, 3001},
  {0x3b58, 1904},
  {0x3b59, 2039},
  {0x3b5e, 2211},
  {0x3b5f, 2429},
  {0x3b60, 2439},
  {0x3b61, 2478},
  {0x3b64, 3265},
  {0x3b65, 3492},
  {0x3b66, 3510},
  {0x3b6a, 3845},
  {0x3b73, 2435},
  {0x3b75, 5428},
  {0x3b76, 272},
  {0x3b7a, 1281},
  {0x3b7d, 1903},
  {0x3b7e, 2126},
  /* row 28 */
  {0x3c21, 638},
  {0x3c27, 3209},
  {0x3c28, 3228},
  {0x3c2a, 3697},
  {0x3c2b, 3841},
  {0x3c2d, 3860},
  {0x3c2f, 5375},
  {0x3c30, 1556},
  {0x3c34, 4619},
  {0x3c37, 261},
  {0x3c3c, 1300},
  {0x3c3e, 2631},
  {0x3c41, 4518},
  {0x3c42, 1297},
  {0x3c4d, 4603},
  {0x3c50, 2074},
  {0x3c54, 3685},
  {0x3c56, 4608},
  {0x3c5c, 1377},
  {0x3c61, 4809},
  {0x3c63, 3926},
  {0x3c67, 285},
  {0x3c68, 3699},
  {0x3c6a, 1827},
  {0x3c6f, 3295},
  {0x3c72, 2573},
  {0x3c73, 5186},
  {0x3c7e, 622},
  /* row 29 */
  {0x3d29, 3273},
  {0x3d2a, 3521},
  {0x3d2e, 3863},
  {0x3d39, 4798},
  {0x3d3d, 768},
  {0x3d3e, 1613},
  {0x3d44, 3597},
  {0x3d45, 224},
  {0x3d50, 97},
  {0x3d51, 1621},
  {0x3d55, 2122},
  {0x3d60, 791},
  {0x3d63, 3509},
  {0x3d68, 1162},
  {0x3d6b, 2138},
  {0x3d71, 3719},
  {0x3d77, 1185},
  {0x3d7c, 4993},
  /* row 30 */
  {0x3e26, 321},
  {0x3e2e, 1355},
  {0x3e2f, 166},
  {0x3e3d, 2137},
  {0x3e3e, 2212},
  {0x3e46, 2772},
  {0x3e4b, 3192},
  {0x3e4e, 3280},
  {0x3e57, 1638},
  {0x3e5a, 4341},
  {0x3e5d, 4472},
  {0x3e65, 798},
  {0x3e68, 223},
  {0x3e6c, 1113},
  {0x3e6f, 1364},
  {0x3e75, 2839},
  {0x3e78, 4002},
  /* row 31 */
  {0x3f22, 2303},
  {0x3f27, 3889},
  {0x3f29, 5154},
  {0x3f2d, 403},
  {0x3f34, 1645},
  {0x3f36, 1920},
  {0x3f37, 2080},
  {0x3f39, 2301},
  {0x3f3f, 783},
  {0x3f43, 3837},
  {0x3f48, 4601},
  {0x3f49, 4646},
  {0x3f4a, 4709},
  {0x3f4c, 5055},
  {0x3f4d, 339},
  {0x3f5e, 1034},
  {0x3f62, 211},
  {0x3f65, 2482},
  {0x3f69, 3676},
  {0x3f74, 2057},
  /* row 32 */
  {0x402d, 1666},
  {0x402e, 1799},
  {0x4030, 2436},
  {0x4031, 2121},
  {0x4032, 2143},
  {0x4035, 27},
  {0x4038, 2991},
  {0x403e, 4273},
  {0x4044, 5076},
  {0x4045, 5077},
  {0x404e, 2108},
  {0x404f, 2194},
  {0x4050, 3176},
  {0x4051, 3306},
  {0x4056, 4534},
  {0x405a, 667},
  {0x405c, 1951},
  {0x405e, 1855},
  {0x4063, 5044},
  {0x4064, 3539},
  {0x4065, 3855},
  {0x4068, 571},
  {0x4069, 156},
  {0x406e, 1447},
  {0x4070, 1823},
  {0x407e, 3580},
  /* row 33 */
  {0x4125, 3873},
  {0x4130, 595},
  {0x4133, 2770},
  {0x4134, 384},
  {0x4147, 3511},
  {0x4148, 3520},
  {0x4150, 859},
  {0x4158, 1402},
  {0x415b, 1728},
  {0x4161, 2100},
  {0x416a, 2241},
  {0x416d, 3567},
  {0x4170, 3939},
  {0x4175, 4234},
  {0x4176, 4539},
  {0x417c, 540},
  {0x417d, 1137},
  /* row 34 */
  {0x4224, 4701},
  {0x4226, 509},
  {0x422b, 196},
  {0x422c, 2632},
  {0x422d, 4546},
  {0x422e, 4700},
  {0x4233, 3544},
  {0x4236, 590},
  {0x4238, 1267},
  {0x423e, 361},
  {0x423f, 1169},
  {0x4240, 1172},
  {0x424a, 2313},
  {0x424e, 405},
  {0x4250, 2067},
  {0x4256, 1743},
  {0x4265, 364},
  {0x4267, 1171},
  {0x4268, 3385},
  {0x426a, 2164},
  {0x426c, 2655},
  {0x4274, 2503},
  /* row 35 */
  {0x4323, 4721},
  {0x432b, 4458},
  {0x432f, 4384},
  {0x4331, 139},
  {0x433a, 1418},
  {0x433b, 3172},
  {0x4346, 1575},
  {0x434b, 2996},
  {0x434d, 488},
  {0x434e, 3169},
  {0x434f, 1056},
  {0x4356, 3644},
  {0x4359, 4722},
  {0x435d, 3366},
  {0x4362, 3325},
  {0x4363, 3940},
  {0x4365, 3665},
  {0x4366, 81},
  {0x4368, 1291},
  {0x436b, 53},
  {0x436c, 2236},
  {0x436e, 4115},
  /* row 36 */
  {0x442b, 3788},
  {0x442c, 2702},
  {0x4436, 4543},
  {0x4439, 4938},
  {0x443b, 5340},
  {0x443e, 775},
  {0x444c, 4703},
  {0x4463, 406},
  {0x446a, 1296},
  {0x446c, 1508},
  {0x446d, 1514},
  {0x4472, 1914},
  {0x4478, 3285},
  {0x4479, 3581},
  /* row 37 */
  {0x4526, 1987},
  {0x452a, 3097},
  {0x452f, 931},
  {0x4534, 4844},
  {0x4535, 588},
  {0x4537, 16},
  {0x453e, 4615},
  {0x4540, 804},
  {0x4544, 2994},
  {0x4545, 5050},
  {0x454c, 1614},
  {0x4559, 1511},
  {0x455a, 1050},
  {0x455f, 1161},
  {0x4561, 665},
  {0x4563, 1109},
  {0x4567, 230},
  {0x456c, 213},
  {0x4574, 2745},
  {0x4576, 1359},
  {0x4579, 3396},
  /* row 38 */
  {0x4626, 4465},
  {0x4630, 730},
  {0x4631, 619},
  {0x4633, 1354},
  {0x463b, 4724},
  {0x463c, 4853},
  {0x4643, 2860},
  {0x4649, 4375},
  {0x465e, 2160},
  {0x4662, 82},
  {0x466e, 778},
  {0x4671, 5038},
  {0x4673, 273},
  {0x4679, 3724},
  {0x467c, 2097},
  {0x467e, 574},
  /* row 39 */
  {0x4721, 1189},
  {0x472e, 2797},
  {0x472f, 188},
  {0x4733, 2808},
  {0x4734, 3472},
  {0x4748, 2529},
  {0x474f, 5191},
  {0x4769, 3275},
  {0x4772, 3095},
  {0x477e, 5385},
  /* row 40 */
  {0x4821, 49},
  {0x482c, 577},
  {0x482f, 3092},
  {0x483e, 132},
  {0x483f, 817},
  {0x4841, 1469},
  {0x484c, 3865},
  {0x4856, 4811},
  {0x4860, 1604},
  {0x4866, 2470},
  {0x4869, 3109},
  {0x4873, 5080},
  {0x4874, 5152},
  {0x4878, 1383},
  {0x4879, 1631},
  {0x487e, 3658},
  /* row 41 */
  {0x4921, 5421},
  {0x492e, 3397},
  {0x4934, 33},
  {0x4938, 2359},
  {0x4939, 131},
  {0x493d, 108},
  {0x4942, 3042},
  {0x4943, 3271},
  {0x494a, 923},
  {0x4954, 17},
  {0x495b, 1468},
  {0x4963, 2832},
  {0x4969, 4488},
  {0x4977, 5148},
  {0x497d, 1484},
  /* row 42 */
  {0x4a23, 4255},
  {0x4a26, 173},
  {0x4a2a, 2857},
  {0x4a2c, 578},
  {0x4a38, 2064},
  {0x4a39, 4959},
  {0x4a3f, 26},
  {0x4a42, 589},
  {0x4a44, 4945},
  {0x4a46, 3461},
  {0x4a50, 511},
  {0x4a51, 306},
  {0x4a52, 2842},
  {0x4a55, 4661},
  {0x4a6c, 2466},
  {0x4a7c, 2084},
  {0x4a7d, 2082},
  /* row 43 */
  {0x4b21, 2535},
  {0x4b26, 3749},
  {0x4b4c, 751},
  {0x4b4f, 5404},
  {0x4b5c, 96},
  {0x4b63, 5390},
  {0x4b68, 2467},
  {0x4b74, 855},
  {0x4b7c, 7},
  /* row 44 */
  {0x4c23, 913},
  {0x4c24, 179},
  {0x4c29, 1316},
  {0x4c35, 2773},
  {0x4c37, 3164},
  {0x4c3e, 1170},
  {0x4c40, 2110},
  {0x4c4c, 5087},
  {0x4c53, 2473},
  {0x4c5a, 2170},
  {0x4c5c, 3127},
  {0x4c64, 4944},
  {0x4c67, 4940},
  {0x4c6b, 298},
  {0x4c70, 3168},
  {0x4c72, 1598},
  {0x4c74, 4074},
  {0x4c78, 2233},
  {0x4c7d, 2534},
  /* row 45 */
  {0x4d2d, 3727},
  {0x4d30, 2565},
  {0x4d3a, 5030},
  {0x4d3c, 1167},
  {0x4d3e, 408},
  {0x4d4f, 2659},
  {0x4d51, 2993},
  {0x4d53, 3656},
  {0x4d55, 4001},
  {0x4d57, 4274},
  {0x4d5b, 5012},
  {0x4d63, 3680},
  {0x4d68, 202},
  {0x4d6b, 5049},
  {0x4d70, 3856},
  {0x4d71, 199},
  {0x4d72, 1431},
  {0x4d78, 3264},
  {0x4d7d, 2942},
  /* row 46 */
  {0x4e24, 4813},
  {0x4e25, 5040},
  {0x4e26, 5005},
  {0x4e28, 319},
  {0x4e29, 3343},
  {0x4e2e, 2576},
  {0x4e32, 3191},
  {0x4e33, 3471},
  {0x4e35, 5440},
  {0x4e3e, 34},
  {0x4e41, 3468},
  {0x4e49, 3885},
  {0x4e4c, 2141},
  {0x4e4f, 715},
  {0x4e53, 2210},
  {0x4e55, 2807},
  {0x4e58, 4630},
  {0x4e60, 5138},
  {0x4e63, 428},
  {0x4e64, 642},
  {0x4e6d, 5048},
  {0x4e6e, 5056},
  {0x4e73, 2438},
  /* row 47 */
  {0x4f22, 4702},
  {0x4f27, 2750},
  {0x4f29, 4561},
  {0x4f37, 3683},
  {0x4f3b, 283},
  {0x4f40, 4391},
  {0x4f42, 3268},
  {0x4f43, 4358},
  {0x4f44, 54},
  {0x4f47, 1710},
  /* 7 additional Level 2 Kanji */
  {0x534c, 973},		/* row 51 */
  {0x5879, 1794},		/* row 56 */
  {0x5960, 1942},		/* row 57 */
  {0x626f, 3200},		/* row 66 */
  {0x6446, 3458},		/* row 68 */
  {0x6647, 5083},		/* row 70 */
  {0x6d55, 4633},		/* row 77 */
  {0, 0}
};

/* Non-Kanji characters in the JIS character set.  We map nearly all of
   these into characters (in the 0..255 range) in our existing fonts, which
   are laid out in g_fontdb.c.  If RAW_HERSHEY_GLYPH bit is set, the font
   is ignored, since the character is to be mapped directly to a Hershey
   glyph (presumably one that appears in no font). */

struct jis_entry
{
  int jis, font;
  unsigned short charnum;
};

static const struct jis_entry _builtin_jis_chars[] =
{
/* Row 1 [misc.] */
  {0x2121, HERSHEY_SERIF, RAW_HERSHEY_GLYPH + 4399}, /* full-width space */
  {0x2122, HERSHEY_HIRAGANA, 0x79},
  {0x2123, HERSHEY_HIRAGANA, 0x7a},
  {0x2124, HERSHEY_SERIF, ','},
  {0x2125, HERSHEY_SERIF, '.'},
  {0x2126, HERSHEY_SERIF, 0xb7},
  {0x2127, HERSHEY_SERIF, ':'},
  {0x2128, HERSHEY_SERIF, ';'},
  {0x2129, HERSHEY_SERIF, '?'},
  {0x212a, HERSHEY_SERIF, '!'},
  /* 0x212b..0x212c are Japanese diacritics, shifted left */
  {0x212d, HERSHEY_SERIF, RAW_HERSHEY_GLYPH + 4180},
  {0x212e, HERSHEY_SERIF, RAW_HERSHEY_GLYPH + 4181},
  {0x212f, HERSHEY_SERIF, RAW_HERSHEY_GLYPH + 4182},
  {0x2130, HERSHEY_SERIF, RAW_HERSHEY_GLYPH + 4184},
  {0x2131, HERSHEY_SERIF, RAW_HERSHEY_GLYPH + 4008},
  {0x2132, HERSHEY_SERIF, RAW_HERSHEY_GLYPH + 4012},
  /* 0x2133..0x213a are Japanese characters */
  {0x213b, HERSHEY_SERIF, RAW_HERSHEY_GLYPH + 903},
  {0x213c, HERSHEY_KATAKANA, 0x78},
  {0x213d, HERSHEY_SERIF, '-'},
  {0x213e, HERSHEY_SERIF, 0xad},
  {0x213f, HERSHEY_SERIF, '/'},
  {0x2140, HERSHEY_SERIF, '\\'},
  {0x2141, HERSHEY_SERIF, '~'},
  {0x2142, HERSHEY_SERIF, RAW_HERSHEY_GLYPH + 2230},
  {0x2143, HERSHEY_SERIF, '|'},
  {0x2144, HERSHEY_SERIF, RAW_HERSHEY_GLYPH + 276},
  {0x2145, HERSHEY_SERIF, RAW_HERSHEY_GLYPH + 238},
  {0x2146, HERSHEY_SERIF, '`'},
  {0x2147, HERSHEY_SERIF, '\''},
  {0x2148, HERSHEY_SERIF, '`'},		/* should be double quotes, fixme */
  {0x2149, HERSHEY_SERIF, '\''},		/* same */
  {0x214a, HERSHEY_SERIF, '('},
  {0x214b, HERSHEY_SERIF, ')'},
  {0x214c, HERSHEY_SERIF, '['},		/* should be `bent' brackets, fixme */
  {0x214d, HERSHEY_SERIF, ']'},		/* same */
  {0x214e, HERSHEY_SERIF, '['},
  {0x214f, HERSHEY_SERIF, ']'},
  {0x2150, HERSHEY_SERIF, '{'},
  {0x2151, HERSHEY_SERIF, '}'},
  {0x2152, HERSHEY_SERIF_SYMBOL, 0xe1},
  {0x2153, HERSHEY_SERIF_SYMBOL, 0xf1},
  /* 0x2154..0x2155 are double angle brackets */
  {0x2156, HERSHEY_SERIF_SYMBOL, 0xe9},
  {0x2157, HERSHEY_SERIF_SYMBOL, 0xfb},
  {0x2158, HERSHEY_SERIF_SYMBOL, 0xe9},		/* should be outlined \lc and \rf, fixme */
  {0x2159, HERSHEY_SERIF_SYMBOL, 0xfb},		/* same */
  {0x215a, HERSHEY_SERIF_BOLD, '['},		/* shouldn't be ordinary bold brackets, fixme */
  {0x215b, HERSHEY_SERIF_BOLD, ']'},		/* same */
  {0x215c, HERSHEY_SERIF, '+'},
  {0x215d, HERSHEY_SERIF, '-'},
  {0x215e, HERSHEY_SERIF_SYMBOL, 0xb1},
  {0x215f, HERSHEY_SERIF, 0xd7},
  {0x2160, HERSHEY_SERIF, 0xf7},
  {0x2161, HERSHEY_SERIF, '='},
  {0x2162, HERSHEY_SERIF_SYMBOL, 0xb9},
  {0x2163, HERSHEY_SERIF, '<'},
  {0x2164, HERSHEY_SERIF, '>'},
  {0x2165, HERSHEY_SERIF_SYMBOL, 0xa3},
  {0x2166, HERSHEY_SERIF_SYMBOL, 0xb3},
  {0x2167, HERSHEY_SERIF_SYMBOL, 0xa5},
  {0x2168, HERSHEY_SERIF_SYMBOL, 0x5c},
  {0x2169, HERSHEY_SERIF, RAW_HERSHEY_GLYPH + 2285},
  {0x216a, HERSHEY_SERIF, RAW_HERSHEY_GLYPH + 2283},
  {0x216b, HERSHEY_SERIF_SYMBOL, 0xb0},
  {0x216c, HERSHEY_SERIF_SYMBOL, 0xa2},
  {0x216d, HERSHEY_SERIF_SYMBOL, 0xb2},
  /* 0x216e is degrees centigrade */
  {0x216f, HERSHEY_SERIF, 0xa5},
  {0x2170, HERSHEY_SERIF, '$'},
  {0x2171, HERSHEY_SERIF, 0xa2},
  {0x2172, HERSHEY_SERIF, 0xa3},
  {0x2173, HERSHEY_SERIF, '%'},
  {0x2174, HERSHEY_SERIF, '#'},
  {0x2175, HERSHEY_SERIF, '&'},
  {0x2176, HERSHEY_SERIF, '*'},
  {0x2177, HERSHEY_SERIF, '@'},
  {0x2178, HERSHEY_SERIF, 0xa7},
  {0x2179, HERSHEY_SERIF, RAW_HERSHEY_GLYPH + 844},
  {0x217a, HERSHEY_SERIF, RAW_HERSHEY_GLYPH + 856},
  {0x217b, HERSHEY_SERIF, RAW_HERSHEY_GLYPH + 901},
  {0x217c, HERSHEY_SERIF, RAW_HERSHEY_GLYPH + 850}, /* should be filled circle */
  {0x217d, HERSHEY_SERIF, RAW_HERSHEY_GLYPH + 4109},
  {0x217e, HERSHEY_SERIF_SYMBOL, 0xe0},	/* lozenge rather than square; OK? */
/* Row 2 [misc.] */
  /* 0x2220..0x2229 are mostly squares, triangles */
  {0x222a, HERSHEY_SERIF_SYMBOL, 0xae},
  {0x222b, HERSHEY_SERIF_SYMBOL, 0xac},
  {0x222c, HERSHEY_SERIF_SYMBOL, 0xad},
  {0x222d, HERSHEY_SERIF_SYMBOL, 0xaf},
  {0x222d, HERSHEY_SERIF_BOLD, '='},	/* 0x222e is two bold horizontal strokes, NOT bold = */
  {0x223a, HERSHEY_SERIF_SYMBOL, 0xce},
  {0x223b, HERSHEY_SERIF_SYMBOL, RAW_HERSHEY_GLYPH + 282},
  {0x223c, HERSHEY_SERIF_SYMBOL, 0xcd},
  {0x223d, HERSHEY_SERIF_SYMBOL, 0xca},
  {0x223e, HERSHEY_SERIF_SYMBOL, 0xcc},
  {0x223f, HERSHEY_SERIF_SYMBOL, 0xc9},
  {0x2240, HERSHEY_SERIF_SYMBOL, 0xc8},
  {0x2241, HERSHEY_SERIF_SYMBOL, 0xc7},
  {0x224a, HERSHEY_SERIF_SYMBOL, 0xd9},
  {0x224b, HERSHEY_SERIF_SYMBOL, 0xda},
  {0x224c, HERSHEY_SERIF,  0xac},
  {0x224d, HERSHEY_SERIF_SYMBOL, 0xde},
  {0x224e, HERSHEY_SERIF_SYMBOL, 0xdb},
  {0x224f, HERSHEY_SERIF_SYMBOL, 0x22},
  {0x2250, HERSHEY_SERIF_SYMBOL, 0x24},
  {0x225c, HERSHEY_SERIF_SYMBOL, 0xb0},
  {0x225d, HERSHEY_SERIF_SYMBOL, 0x5e},
  {0x225e, HERSHEY_SERIF, RAW_HERSHEY_GLYPH + 4008},
  {0x225f, HERSHEY_SERIF_SYMBOL, 0xb6},
  {0x2260, HERSHEY_SERIF_SYMBOL, 0xd1},
  {0x2261, HERSHEY_SERIF_SYMBOL, 0xba},
  {0x2262, HERSHEY_SERIF, RAW_HERSHEY_GLYPH + 276},
  /* 0x2263..0x2264 are \ll and \gg */
  {0x2265, HERSHEY_SERIF_SYMBOL, 0xd6},
  {0x2266, HERSHEY_SERIF, RAW_HERSHEY_GLYPH + 4133},
  {0x2267, HERSHEY_SERIF_SYMBOL, 0xb5},
  {0x2268, HERSHEY_SERIF, RAW_HERSHEY_GLYPH + 4132},
  {0x2269, HERSHEY_SERIF_SYMBOL, 0xf2},
  /* 0x2270 is a double integral */
  {0x2272, HERSHEY_SERIF, 0xc5},
  /* 0x2273 is perthousand */
  {0x2274, HERSHEY_SERIF, RAW_HERSHEY_GLYPH + 2323},
  {0x2275, HERSHEY_SERIF, RAW_HERSHEY_GLYPH + 2325},
  /* 0x2276 is an eighth note */
  {0x2277, HERSHEY_SERIF, RAW_HERSHEY_GLYPH + 2277},
  {0x2278, HERSHEY_SERIF, RAW_HERSHEY_GLYPH + 2278},
  {0x2279, HERSHEY_SERIF, 0xb6},
  {0x227e, HERSHEY_SERIF, RAW_HERSHEY_GLYPH + 905},
/* Row 3 [Roman characters], taken from HersheySerif */
  {0x2330, HERSHEY_SERIF, '0'},
  {0x2331, HERSHEY_SERIF, '1'},
  {0x2332, HERSHEY_SERIF, '2'},
  {0x2333, HERSHEY_SERIF, '3'},
  {0x2334, HERSHEY_SERIF, '4'},
  {0x2335, HERSHEY_SERIF, '5'},
  {0x2336, HERSHEY_SERIF, '6'},
  {0x2337, HERSHEY_SERIF, '7'},
  {0x2338, HERSHEY_SERIF, '8'},
  {0x2339, HERSHEY_SERIF, '9'},
  {0x2341, HERSHEY_SERIF, 'A'},
  {0x2342, HERSHEY_SERIF, 'B'},
  {0x2343, HERSHEY_SERIF, 'C'},
  {0x2344, HERSHEY_SERIF, 'D'},
  {0x2345, HERSHEY_SERIF, 'E'},
  {0x2346, HERSHEY_SERIF, 'F'},
  {0x2347, HERSHEY_SERIF, 'G'},
  {0x2348, HERSHEY_SERIF, 'H'},
  {0x2349, HERSHEY_SERIF, 'I'},
  {0x234a, HERSHEY_SERIF, 'J'},
  {0x234b, HERSHEY_SERIF, 'K'},
  {0x234c, HERSHEY_SERIF, 'L'},
  {0x234d, HERSHEY_SERIF, 'M'},
  {0x234e, HERSHEY_SERIF, 'N'},
  {0x234f, HERSHEY_SERIF, 'O'},
  {0x2350, HERSHEY_SERIF, 'P'},
  {0x2351, HERSHEY_SERIF, 'Q'},
  {0x2352, HERSHEY_SERIF, 'R'},
  {0x2353, HERSHEY_SERIF, 'S'},
  {0x2354, HERSHEY_SERIF, 'T'},
  {0x2355, HERSHEY_SERIF, 'U'},
  {0x2356, HERSHEY_SERIF, 'V'},
  {0x2357, HERSHEY_SERIF, 'W'},
  {0x2358, HERSHEY_SERIF, 'X'},
  {0x2359, HERSHEY_SERIF, 'Y'},
  {0x235a, HERSHEY_SERIF, 'Z'},
  {0x2361, HERSHEY_SERIF, 'a'},
  {0x2362, HERSHEY_SERIF, 'b'},
  {0x2363, HERSHEY_SERIF, 'c'},
  {0x2364, HERSHEY_SERIF, 'd'},
  {0x2365, HERSHEY_SERIF, 'e'},
  {0x2366, HERSHEY_SERIF, 'f'},
  {0x2367, HERSHEY_SERIF, 'g'},
  {0x2368, HERSHEY_SERIF, 'h'},
  {0x2369, HERSHEY_SERIF, 'i'},
  {0x236a, HERSHEY_SERIF, 'j'},
  {0x236b, HERSHEY_SERIF, 'k'},
  {0x236c, HERSHEY_SERIF, 'l'},
  {0x236d, HERSHEY_SERIF, 'm'},
  {0x236e, HERSHEY_SERIF, 'n'},
  {0x236f, HERSHEY_SERIF, 'o'},
  {0x2370, HERSHEY_SERIF, 'p'},
  {0x2371, HERSHEY_SERIF, 'q'},
  {0x2372, HERSHEY_SERIF, 'r'},
  {0x2373, HERSHEY_SERIF, 's'},
  {0x2374, HERSHEY_SERIF, 't'},
  {0x2375, HERSHEY_SERIF, 'u'},
  {0x2376, HERSHEY_SERIF, 'v'},
  {0x2377, HERSHEY_SERIF, 'w'},
  {0x2378, HERSHEY_SERIF, 'x'},
  {0x2379, HERSHEY_SERIF, 'y'},
  {0x237a, HERSHEY_SERIF, 'z'},
/* Row 4 [Hiragana], taken from HersheyHiragana. */
  {0x2421, HERSHEY_HIRAGANA, 0x21},
  {0x2422, HERSHEY_HIRAGANA, 0x22},
  {0x2423, HERSHEY_HIRAGANA, 0x23},
  {0x2424, HERSHEY_HIRAGANA, 0x24},
  {0x2425, HERSHEY_HIRAGANA, 0x25},
  {0x2426, HERSHEY_HIRAGANA, 0x26},
  {0x2427, HERSHEY_HIRAGANA, 0x27},
  {0x2428, HERSHEY_HIRAGANA, 0x28},
  {0x2429, HERSHEY_HIRAGANA, 0x29},
  {0x242a, HERSHEY_HIRAGANA, 0x2a},
  {0x242b, HERSHEY_HIRAGANA, 0x2b},
  {0x242c, HERSHEY_HIRAGANA, 0x2c},
  {0x242d, HERSHEY_HIRAGANA, 0x2d},
  {0x242e, HERSHEY_HIRAGANA, 0x2e},
  {0x242f, HERSHEY_HIRAGANA, 0x2f},
  {0x2430, HERSHEY_HIRAGANA, 0x30},
  {0x2431, HERSHEY_HIRAGANA, 0x31},
  {0x2432, HERSHEY_HIRAGANA, 0x32},
  {0x2433, HERSHEY_HIRAGANA, 0x33},
  {0x2434, HERSHEY_HIRAGANA, 0x34},
  {0x2435, HERSHEY_HIRAGANA, 0x35},
  {0x2436, HERSHEY_HIRAGANA, 0x36},
  {0x2437, HERSHEY_HIRAGANA, 0x37},
  {0x2438, HERSHEY_HIRAGANA, 0x38},
  {0x2439, HERSHEY_HIRAGANA, 0x39},
  {0x243a, HERSHEY_HIRAGANA, 0x3a},
  {0x243b, HERSHEY_HIRAGANA, 0x3b},
  {0x243c, HERSHEY_HIRAGANA, 0x3c},
  {0x243d, HERSHEY_HIRAGANA, 0x3d},
  {0x243e, HERSHEY_HIRAGANA, 0x3e},
  {0x243f, HERSHEY_HIRAGANA, 0x3f},
  {0x2440, HERSHEY_HIRAGANA, 0x40},
  {0x2441, HERSHEY_HIRAGANA, 0x41},
  {0x2442, HERSHEY_HIRAGANA, 0x42},
  {0x2443, HERSHEY_HIRAGANA, 0x43},
  {0x2444, HERSHEY_HIRAGANA, 0x44},
  {0x2445, HERSHEY_HIRAGANA, 0x45},
  {0x2446, HERSHEY_HIRAGANA, 0x46},
  {0x2447, HERSHEY_HIRAGANA, 0x47},
  {0x2448, HERSHEY_HIRAGANA, 0x48},
  {0x2449, HERSHEY_HIRAGANA, 0x49},
  {0x244a, HERSHEY_HIRAGANA, 0x4a},
  {0x244b, HERSHEY_HIRAGANA, 0x4b},
  {0x244c, HERSHEY_HIRAGANA, 0x4c},
  {0x244d, HERSHEY_HIRAGANA, 0x4d},
  {0x244e, HERSHEY_HIRAGANA, 0x4e},
  {0x244f, HERSHEY_HIRAGANA, 0x4f},
  {0x2450, HERSHEY_HIRAGANA, 0x50},
  {0x2451, HERSHEY_HIRAGANA, 0x51},
  {0x2452, HERSHEY_HIRAGANA, 0x52},
  {0x2453, HERSHEY_HIRAGANA, 0x53},
  {0x2454, HERSHEY_HIRAGANA, 0x54},
  {0x2455, HERSHEY_HIRAGANA, 0x55},
  {0x2456, HERSHEY_HIRAGANA, 0x56},
  {0x2457, HERSHEY_HIRAGANA, 0x57},
  {0x2458, HERSHEY_HIRAGANA, 0x58},
  {0x2459, HERSHEY_HIRAGANA, 0x59},
  {0x245a, HERSHEY_HIRAGANA, 0x5a},
  {0x245b, HERSHEY_HIRAGANA, 0x5b},
  {0x245c, HERSHEY_HIRAGANA, 0x5c},
  {0x245d, HERSHEY_HIRAGANA, 0x5d},
  {0x245e, HERSHEY_HIRAGANA, 0x5e},
  {0x245f, HERSHEY_HIRAGANA, 0x5f},
  {0x2460, HERSHEY_HIRAGANA, 0x60},
  {0x2461, HERSHEY_HIRAGANA, 0x61},
  {0x2462, HERSHEY_HIRAGANA, 0x62},
  {0x2463, HERSHEY_HIRAGANA, 0x63},
  {0x2464, HERSHEY_HIRAGANA, 0x64},
  {0x2465, HERSHEY_HIRAGANA, 0x65},
  {0x2466, HERSHEY_HIRAGANA, 0x66},
  {0x2467, HERSHEY_HIRAGANA, 0x67},
  {0x2468, HERSHEY_HIRAGANA, 0x68},
  {0x2469, HERSHEY_HIRAGANA, 0x69},
  {0x246a, HERSHEY_HIRAGANA, 0x6a},
  {0x246b, HERSHEY_HIRAGANA, 0x6b},
  {0x246c, HERSHEY_HIRAGANA, 0x6c},
  {0x246d, HERSHEY_HIRAGANA, 0x6d},
  {0x246e, HERSHEY_HIRAGANA, 0x6e},
  {0x246f, HERSHEY_HIRAGANA, 0x6f},
  {0x2470, HERSHEY_HIRAGANA, 0x70},
  {0x2471, HERSHEY_HIRAGANA, 0x71},
  {0x2472, HERSHEY_HIRAGANA, 0x72},
  {0x2473, HERSHEY_HIRAGANA, 0x73},
/* Row 5 [Katakana], taken from HersheyKatakana. */
  {0x2521, HERSHEY_KATAKANA, 0x21},
  {0x2522, HERSHEY_KATAKANA, 0x22},
  {0x2523, HERSHEY_KATAKANA, 0x23},
  {0x2524, HERSHEY_KATAKANA, 0x24},
  {0x2525, HERSHEY_KATAKANA, 0x25},
  {0x2526, HERSHEY_KATAKANA, 0x26},
  {0x2527, HERSHEY_KATAKANA, 0x27},
  {0x2528, HERSHEY_KATAKANA, 0x28},
  {0x2529, HERSHEY_KATAKANA, 0x29},
  {0x252a, HERSHEY_KATAKANA, 0x2a},
  {0x252b, HERSHEY_KATAKANA, 0x2b},
  {0x252c, HERSHEY_KATAKANA, 0x2c},
  {0x252d, HERSHEY_KATAKANA, 0x2d},
  {0x252e, HERSHEY_KATAKANA, 0x2e},
  {0x252f, HERSHEY_KATAKANA, 0x2f},
  {0x2530, HERSHEY_KATAKANA, 0x30},
  {0x2531, HERSHEY_KATAKANA, 0x31},
  {0x2532, HERSHEY_KATAKANA, 0x32},
  {0x2533, HERSHEY_KATAKANA, 0x33},
  {0x2534, HERSHEY_KATAKANA, 0x34},
  {0x2535, HERSHEY_KATAKANA, 0x35},
  {0x2536, HERSHEY_KATAKANA, 0x36},
  {0x2537, HERSHEY_KATAKANA, 0x37},
  {0x2538, HERSHEY_KATAKANA, 0x38},
  {0x2539, HERSHEY_KATAKANA, 0x39},
  {0x253a, HERSHEY_KATAKANA, 0x3a},
  {0x253b, HERSHEY_KATAKANA, 0x3b},
  {0x253c, HERSHEY_KATAKANA, 0x3c},
  {0x253d, HERSHEY_KATAKANA, 0x3d},
  {0x253e, HERSHEY_KATAKANA, 0x3e},
  {0x253f, HERSHEY_KATAKANA, 0x3f},
  {0x2540, HERSHEY_KATAKANA, 0x40},
  {0x2541, HERSHEY_KATAKANA, 0x41},
  {0x2542, HERSHEY_KATAKANA, 0x42},
  {0x2543, HERSHEY_KATAKANA, 0x43},
  {0x2544, HERSHEY_KATAKANA, 0x44},
  {0x2545, HERSHEY_KATAKANA, 0x45},
  {0x2546, HERSHEY_KATAKANA, 0x46},
  {0x2547, HERSHEY_KATAKANA, 0x47},
  {0x2548, HERSHEY_KATAKANA, 0x48},
  {0x2549, HERSHEY_KATAKANA, 0x49},
  {0x254a, HERSHEY_KATAKANA, 0x4a},
  {0x254b, HERSHEY_KATAKANA, 0x4b},
  {0x254c, HERSHEY_KATAKANA, 0x4c},
  {0x254d, HERSHEY_KATAKANA, 0x4d},
  {0x254e, HERSHEY_KATAKANA, 0x4e},
  {0x254f, HERSHEY_KATAKANA, 0x4f},
  {0x2550, HERSHEY_KATAKANA, 0x50},
  {0x2551, HERSHEY_KATAKANA, 0x51},
  {0x2552, HERSHEY_KATAKANA, 0x52},
  {0x2553, HERSHEY_KATAKANA, 0x53},
  {0x2554, HERSHEY_KATAKANA, 0x54},
  {0x2555, HERSHEY_KATAKANA, 0x55},
  {0x2556, HERSHEY_KATAKANA, 0x56},
  {0x2557, HERSHEY_KATAKANA, 0x57},
  {0x2558, HERSHEY_KATAKANA, 0x58},
  {0x2559, HERSHEY_KATAKANA, 0x59},
  {0x255a, HERSHEY_KATAKANA, 0x5a},
  {0x255b, HERSHEY_KATAKANA, 0x5b},
  {0x255c, HERSHEY_KATAKANA, 0x5c},
  {0x255d, HERSHEY_KATAKANA, 0x5d},
  {0x255e, HERSHEY_KATAKANA, 0x5e},
  {0x255f, HERSHEY_KATAKANA, 0x5f},
  {0x2560, HERSHEY_KATAKANA, 0x60},
  {0x2561, HERSHEY_KATAKANA, 0x61},
  {0x2562, HERSHEY_KATAKANA, 0x62},
  {0x2563, HERSHEY_KATAKANA, 0x63},
  {0x2564, HERSHEY_KATAKANA, 0x64},
  {0x2565, HERSHEY_KATAKANA, 0x65},
  {0x2566, HERSHEY_KATAKANA, 0x66},
  {0x2567, HERSHEY_KATAKANA, 0x67},
  {0x2568, HERSHEY_KATAKANA, 0x68},
  {0x2569, HERSHEY_KATAKANA, 0x69},
  {0x256a, HERSHEY_KATAKANA, 0x6a},
  {0x256b, HERSHEY_KATAKANA, 0x6b},
  {0x256c, HERSHEY_KATAKANA, 0x6c},
  {0x256d, HERSHEY_KATAKANA, 0x6d},
  {0x256e, HERSHEY_KATAKANA, 0x6e},
  {0x256f, HERSHEY_KATAKANA, 0x6f},
  {0x2570, HERSHEY_KATAKANA, 0x70},
  {0x2571, HERSHEY_KATAKANA, 0x71},
  {0x2572, HERSHEY_KATAKANA, 0x72},
  {0x2573, HERSHEY_KATAKANA, 0x73},
  {0x2574, HERSHEY_KATAKANA, 0x74},
  {0x2575, HERSHEY_KATAKANA, 0x75},
  {0x2576, HERSHEY_KATAKANA, 0x76},
/* Row 6 [Greek characters], taken from HersheySerif-Symbol. */
  {0x2621, HERSHEY_SERIF_SYMBOL, 'A'},
  {0x2622, HERSHEY_SERIF_SYMBOL, 'B'},
  {0x2623, HERSHEY_SERIF_SYMBOL, 'G'},
  {0x2624, HERSHEY_SERIF_SYMBOL, 'D'},
  {0x2625, HERSHEY_SERIF_SYMBOL, 'E'},
  {0x2626, HERSHEY_SERIF_SYMBOL, 'Z'},
  {0x2627, HERSHEY_SERIF_SYMBOL, 'H'},
  {0x2628, HERSHEY_SERIF_SYMBOL, 'Q'},
  {0x2629, HERSHEY_SERIF_SYMBOL, 'I'},
  {0x262a, HERSHEY_SERIF_SYMBOL, 'K'},
  {0x262b, HERSHEY_SERIF_SYMBOL, 'L'},
  {0x262c, HERSHEY_SERIF_SYMBOL, 'M'},
  {0x262d, HERSHEY_SERIF_SYMBOL, 'N'},
  {0x262e, HERSHEY_SERIF_SYMBOL, 'X'},
  {0x262f, HERSHEY_SERIF_SYMBOL, 'O'},
  {0x2630, HERSHEY_SERIF_SYMBOL, 'P'},
  {0x2631, HERSHEY_SERIF_SYMBOL, 'R'},
  {0x2632, HERSHEY_SERIF_SYMBOL, 'S'},
  {0x2633, HERSHEY_SERIF_SYMBOL, 'T'},
  {0x2634, HERSHEY_SERIF_SYMBOL, 0x80 + '!'},	/* variant upsilon */
  {0x2635, HERSHEY_SERIF_SYMBOL, 'F'},
  {0x2636, HERSHEY_SERIF_SYMBOL, 'C'},
  {0x2637, HERSHEY_SERIF_SYMBOL, 'Y'},
  {0x2638, HERSHEY_SERIF_SYMBOL, 'W'},
  {0x2641, HERSHEY_SERIF_SYMBOL, 'a'},
  {0x2642, HERSHEY_SERIF_SYMBOL, 'b'},
  {0x2643, HERSHEY_SERIF_SYMBOL, 'g'},
  {0x2644, HERSHEY_SERIF_SYMBOL, 'd'},
  {0x2645, HERSHEY_SERIF_SYMBOL, 'e'},
  {0x2646, HERSHEY_SERIF_SYMBOL, 'z'},
  {0x2647, HERSHEY_SERIF_SYMBOL, 'h'},
  {0x2648, HERSHEY_SERIF_SYMBOL, 'q'},
  {0x2649, HERSHEY_SERIF_SYMBOL, 'i'},
  {0x264a, HERSHEY_SERIF_SYMBOL, 'k'},
  {0x264b, HERSHEY_SERIF_SYMBOL, 'l'},
  {0x264c, HERSHEY_SERIF_SYMBOL, 'm'},
  {0x264d, HERSHEY_SERIF_SYMBOL, 'n'},
  {0x264e, HERSHEY_SERIF_SYMBOL, 'x'},
  {0x264f, HERSHEY_SERIF_SYMBOL, 'o'},
  {0x2650, HERSHEY_SERIF_SYMBOL, 'p'},
  {0x2651, HERSHEY_SERIF_SYMBOL, 'r'},
  {0x2652, HERSHEY_SERIF_SYMBOL, 's'},
  {0x2653, HERSHEY_SERIF_SYMBOL, 't'},
  {0x2654, HERSHEY_SERIF_SYMBOL, 'u'},
  {0x2655, HERSHEY_SERIF_SYMBOL, 'f'},
  {0x2656, HERSHEY_SERIF_SYMBOL, 'c'},
  {0x2657, HERSHEY_SERIF_SYMBOL, 'y'},
  {0x2658, HERSHEY_SERIF_SYMBOL, 'w'},
/* Row 7 [Cyrillic characters], taken from HersheyCyrillic.  The strange
   order is because we are mapping to the KOI8-R encoding. */
  {0x2721, HERSHEY_CYRILLIC, 0x80 + 'a'},
  {0x2722, HERSHEY_CYRILLIC, 0x80 + 'b'},
  {0x2723, HERSHEY_CYRILLIC, 0x80 + 'w'},
  {0x2724, HERSHEY_CYRILLIC, 0x80 + 'g'},
  {0x2725, HERSHEY_CYRILLIC, 0x80 + 'd'},
  {0x2726, HERSHEY_CYRILLIC, 0x80 + 'e'},
  {0x2727, HERSHEY_CYRILLIC, 0x80 + '3'},
  {0x2728, HERSHEY_CYRILLIC, 0x80 + 'v'},
  {0x2729, HERSHEY_CYRILLIC, 0x80 + 'z'},
  {0x272a, HERSHEY_CYRILLIC, 0x80 + 'i'},
  {0x272b, HERSHEY_CYRILLIC, 0x80 + 'j'},
  {0x272c, HERSHEY_CYRILLIC, 0x80 + 'k'},
  {0x272d, HERSHEY_CYRILLIC, 0x80 + 'l'},
  {0x272e, HERSHEY_CYRILLIC, 0x80 + 'm'},
  {0x272f, HERSHEY_CYRILLIC, 0x80 + 'n'},
  {0x2730, HERSHEY_CYRILLIC, 0x80 + 'o'},
  {0x2731, HERSHEY_CYRILLIC, 0x80 + 'p'},
  {0x2732, HERSHEY_CYRILLIC, 0x80 + 'r'},
  {0x2733, HERSHEY_CYRILLIC, 0x80 + 's'},
  {0x2734, HERSHEY_CYRILLIC, 0x80 + 't'},
  {0x2735, HERSHEY_CYRILLIC, 0x80 + 'u'},
  {0x2736, HERSHEY_CYRILLIC, 0x80 + 'f'},
  {0x2737, HERSHEY_CYRILLIC, 0x80 + 'h'},
  {0x2738, HERSHEY_CYRILLIC, 0x80 + 'c'},
  {0x2739, HERSHEY_CYRILLIC, 0x80 + '~'},
  {0x273a, HERSHEY_CYRILLIC, 0x80 + '{'},
  {0x273b, HERSHEY_CYRILLIC, 0x80 + '}'},
  {0x273c, HERSHEY_CYRILLIC, 0x80 + 0x7f},
  {0x273d, HERSHEY_CYRILLIC, 0x80 + 'y'},
  {0x273e, HERSHEY_CYRILLIC, 0x80 + 'x'},
  {0x273f, HERSHEY_CYRILLIC, 0x80 + '|'},
  {0x2740, HERSHEY_CYRILLIC, 0x80 + '`'},
  {0x2741, HERSHEY_CYRILLIC, 0x80 + 'q'},
  {0x2751, HERSHEY_CYRILLIC, 0x80 + 'A'},
  {0x2752, HERSHEY_CYRILLIC, 0x80 + 'B'},
  {0x2753, HERSHEY_CYRILLIC, 0x80 + 'W'},
  {0x2754, HERSHEY_CYRILLIC, 0x80 + 'G'},
  {0x2755, HERSHEY_CYRILLIC, 0x80 + 'D'},
  {0x2756, HERSHEY_CYRILLIC, 0x80 + 'E'},
  {0x2757, HERSHEY_CYRILLIC, 0x80 + '#'},
  {0x2758, HERSHEY_CYRILLIC, 0x80 + 'V'},
  {0x2759, HERSHEY_CYRILLIC, 0x80 + 'Z'},
  {0x275a, HERSHEY_CYRILLIC, 0x80 + 'I'},
  {0x275b, HERSHEY_CYRILLIC, 0x80 + 'J'},
  {0x275c, HERSHEY_CYRILLIC, 0x80 + 'K'},
  {0x275d, HERSHEY_CYRILLIC, 0x80 + 'L'},
  {0x275e, HERSHEY_CYRILLIC, 0x80 + 'M'},
  {0x275f, HERSHEY_CYRILLIC, 0x80 + 'N'},
  {0x2760, HERSHEY_CYRILLIC, 0x80 + 'O'},
  {0x2761, HERSHEY_CYRILLIC, 0x80 + 'P'},
  {0x2762, HERSHEY_CYRILLIC, 0x80 + 'R'},
  {0x2763, HERSHEY_CYRILLIC, 0x80 + 'S'},
  {0x2764, HERSHEY_CYRILLIC, 0x80 + 'T'},
  {0x2765, HERSHEY_CYRILLIC, 0x80 + 'U'},
  {0x2766, HERSHEY_CYRILLIC, 0x80 + 'F'},
  {0x2767, HERSHEY_CYRILLIC, 0x80 + 'H'},
  {0x2768, HERSHEY_CYRILLIC, 0x80 + 'C'},
  {0x2769, HERSHEY_CYRILLIC, 0x80 + '^'},
  {0x276a, HERSHEY_CYRILLIC, 0x80 + '['},
  {0x276b, HERSHEY_CYRILLIC, 0x80 + ']'},
  {0x276c, HERSHEY_CYRILLIC, 0x80 + '_'},
  {0x276d, HERSHEY_CYRILLIC, 0x80 + 'Y'},
  {0x276e, HERSHEY_CYRILLIC, 0x80 + 'X'},
  {0x276f, HERSHEY_CYRILLIC, 0x80 + '\\'},
  {0x2770, HERSHEY_CYRILLIC, 0x80 + '@'},
  {0x2771, HERSHEY_CYRILLIC, 0x80 + 'Q'},
  {0, 0, 0}
};

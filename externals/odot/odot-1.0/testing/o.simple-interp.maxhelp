{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 6,
			"minor" : 0,
			"revision" : 4
		}
,
		"rect" : [ 698.0, 48.0, 798.0, 729.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 0,
		"gridsize" : [ 8.0, 8.0 ],
		"gridsnaponopen" : 0,
		"statusbarvisible" : 2,
		"toolbarvisible" : 1,
		"boxanimatetime" : 200,
		"imprint" : 0,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"boxes" : [ 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-20",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 40.0, 333.0, 50.0, 20.0 ],
					"presentation_rect" : [ 40.0, 333.0, 0.0, 0.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-17",
					"linecount" : 6,
					"maxclass" : "o.message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 418.0, 496.0, 358.0, 90.0 ],
					"text" : "/x 100. \n/xx 0. 95.7447 223.404 382.979 553.191 691.489 840.426 1000. \n/yy 0. 0.666667 0.973333 0.56 0.88 0.173333 0.573333 0. \n/a 1. \n/w0 8.8 \n/y 0.0336811 \n",
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-28",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 200.0, 56.0, 37.0, 18.0 ],
					"text" : "clear"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-18",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 136.0, 549.0, 39.0, 20.0 ],
					"text" : "zl rev"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-16",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "float" ],
					"patching_rect" : [ 176.0, 296.0, 32.5, 20.0 ],
					"text" : "t f f"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-15",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 136.0, 525.0, 63.0, 20.0 ],
					"text" : "pack 0. 0."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-14",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "bang", "clear" ],
					"patching_rect" : [ 136.0, 248.0, 53.0, 20.0 ],
					"text" : "t b clear"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-13",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "", "FullPacket" ],
					"patching_rect" : [ 136.0, 485.0, 61.0, 20.0 ],
					"text" : "o.route /y"
				}

			}
, 			{
				"box" : 				{
					"addpoints" : [ 1.0, 0.000036, 0, 2.0, 0.000072, 0, 3.0, 0.000108, 0, 4.0, 0.000145, 0, 5.0, 0.000183, 0, 6.0, 0.000221, 0, 7.0, 0.000259, 0, 8.0, 0.000298, 0, 9.0, 0.000337, 0, 10.0, 0.000377, 0, 11.0, 0.000417, 0, 12.0, 0.000458, 0, 13.0, 0.0005, 0, 14.0, 0.000542, 0, 15.0, 0.000584, 0, 16.0, 0.000628, 0, 17.0, 0.000671, 0, 18.0, 0.000716, 0, 19.0, 0.000761, 0, 20.0, 0.000807, 0, 21.0, 0.000853, 0, 22.0, 0.000901, 0, 23.0, 0.000949, 0, 24.0, 0.000998, 0, 25.0, 0.001048, 0, 26.0, 0.001098, 0, 27.0, 0.00115, 0, 28.0, 0.001202, 0, 29.0, 0.001256, 0, 30.0, 0.00131, 0, 31.0, 0.001366, 0, 32.0, 0.001422, 0, 33.0, 0.00148, 0, 34.0, 0.001539, 0, 35.0, 0.001599, 0, 36.0, 0.001661, 0, 37.0, 0.001724, 0, 38.0, 0.001788, 0, 39.0, 0.001854, 0, 40.0, 0.001922, 0, 41.0, 0.001991, 0, 42.0, 0.002062, 0, 43.0, 0.002135, 0, 44.0, 0.002209, 0, 45.0, 0.002286, 0, 46.0, 0.002365, 0, 47.0, 0.002447, 0, 48.0, 0.00253, 0, 49.0, 0.002617, 0, 50.0, 0.002706, 0, 51.0, 0.002798, 0, 52.0, 0.002893, 0, 53.0, 0.002992, 0, 54.0, 0.003094, 0, 55.0, 0.0032, 0, 56.0, 0.00331, 0, 57.0, 0.003424, 0, 58.0, 0.003543, 0, 59.0, 0.003667, 0, 60.0, 0.003797, 0, 61.0, 0.003933, 0, 62.0, 0.004075, 0, 63.0, 0.004224, 0, 64.0, 0.004381, 0, 65.0, 0.004546, 0, 66.0, 0.004721, 0, 67.0, 0.004906, 0, 68.0, 0.005102, 0, 69.0, 0.00531, 0, 70.0, 0.005533, 0, 71.0, 0.005771, 0, 72.0, 0.006027, 0, 73.0, 0.006302, 0, 74.0, 0.0066, 0, 75.0, 0.006923, 0, 76.0, 0.007276, 0, 77.0, 0.007663, 0, 78.0, 0.008089, 0, 79.0, 0.008562, 0, 80.0, 0.009091, 0, 81.0, 0.009686, 0, 82.0, 0.010362, 0, 83.0, 0.011137, 0, 84.0, 0.012037, 0, 85.0, 0.013094, 0, 86.0, 0.014358, 0, 87.0, 0.015897, 0, 88.0, 0.017814, 0, 89.0, 0.020273, 0, 90.0, 0.023546, 0, 91.0, 0.02813, 0, 92.0, 0.035018, 0, 93.0, 0.046557, 0, 94.0, 0.069919, 0, 95.0, 0.142614, 0, 96.0, 0.295054, 0, 97.0, 0.094947, 0, 98.0, 0.05786, 0, 99.0, 0.042261, 0, 100.0, 0.033681, 0, 101.0, 0.028261, 0, 102.0, 0.024532, 0, 103.0, 0.021815, 0, 104.0, 0.01975, 0, 105.0, 0.018131, 0, 106.0, 0.016829, 0, 107.0, 0.015763, 0, 108.0, 0.014874, 0, 109.0, 0.014125, 0, 110.0, 0.013486, 0, 111.0, 0.012935, 0, 112.0, 0.012457, 0, 113.0, 0.01204, 0, 114.0, 0.011673, 0, 115.0, 0.011349, 0, 116.0, 0.011062, 0, 117.0, 0.010807, 0, 118.0, 0.01058, 0, 119.0, 0.010376, 0, 120.0, 0.010194, 0, 121.0, 0.010031, 0, 122.0, 0.009884, 0, 123.0, 0.009753, 0, 124.0, 0.009636, 0, 125.0, 0.00953, 0, 126.0, 0.009437, 0, 127.0, 0.009353, 0, 128.0, 0.009279, 0, 129.0, 0.009213, 0, 130.0, 0.009156, 0, 131.0, 0.009106, 0, 132.0, 0.009063, 0, 133.0, 0.009026, 0, 134.0, 0.008996, 0, 135.0, 0.008971, 0, 136.0, 0.008952, 0, 137.0, 0.008938, 0, 138.0, 0.00893, 0, 139.0, 0.008925, 0, 140.0, 0.008926, 0, 141.0, 0.008931, 0, 142.0, 0.00894, 0, 143.0, 0.008953, 0, 144.0, 0.00897, 0, 145.0, 0.008992, 0, 146.0, 0.009017, 0, 147.0, 0.009045, 0, 148.0, 0.009078, 0, 149.0, 0.009114, 0, 150.0, 0.009154, 0, 151.0, 0.009197, 0, 152.0, 0.009245, 0, 153.0, 0.009295, 0, 154.0, 0.00935, 0, 155.0, 0.009408, 0, 156.0, 0.00947, 0, 157.0, 0.009535, 0, 158.0, 0.009605, 0, 159.0, 0.009678, 0, 160.0, 0.009755, 0, 161.0, 0.009837, 0, 162.0, 0.009922, 0, 163.0, 0.010012, 0, 164.0, 0.010106, 0, 165.0, 0.010205, 0, 166.0, 0.010308, 0, 167.0, 0.010416, 0, 168.0, 0.010529, 0, 169.0, 0.010648, 0, 170.0, 0.010772, 0, 171.0, 0.010902, 0, 172.0, 0.011037, 0, 173.0, 0.011179, 0, 174.0, 0.011328, 0, 175.0, 0.011483, 0, 176.0, 0.011646, 0, 177.0, 0.011816, 0, 178.0, 0.011995, 0, 179.0, 0.012182, 0, 180.0, 0.012378, 0, 181.0, 0.012584, 0, 182.0, 0.012801, 0, 183.0, 0.013029, 0, 184.0, 0.013268, 0, 185.0, 0.013521, 0, 186.0, 0.013787, 0, 187.0, 0.014068, 0, 188.0, 0.014365, 0, 189.0, 0.01468, 0, 190.0, 0.015013, 0, 191.0, 0.015367, 0, 192.0, 0.015743, 0, 193.0, 0.016144, 0, 194.0, 0.016571, 0, 195.0, 0.017029, 0, 196.0, 0.017519, 0, 197.0, 0.018046, 0, 198.0, 0.018614, 0, 199.0, 0.019227, 0, 200.0, 0.019892, 0, 201.0, 0.020614, 0, 202.0, 0.021403, 0, 203.0, 0.022267, 0, 204.0, 0.023217, 0, 205.0, 0.024268, 0, 206.0, 0.025437, 0, 207.0, 0.026744, 0, 208.0, 0.028215, 0, 209.0, 0.029884, 0, 210.0, 0.031793, 0, 211.0, 0.034, 0, 212.0, 0.036579, 0, 213.0, 0.039633, 0, 214.0, 0.043308, 0, 215.0, 0.047816, 0, 216.0, 0.053476, 0, 217.0, 0.060796, 0, 218.0, 0.070634, 0, 219.0, 0.084562, 0, 220.0, 0.105806, 0, 221.0, 0.142189, 0, 222.0, 0.218881, 0, 223.0, 0.486191, 0, 224.0, 0.394338, 0, 225.0, 0.199846, 0, 226.0, 0.135238, 0, 227.0, 0.102981, 0, 228.0, 0.083644, 0, 229.0, 0.070762, 0, 230.0, 0.061567, 0, 231.0, 0.054676, 0, 232.0, 0.04932, 0, 233.0, 0.045038, 0, 234.0, 0.041538, 0, 235.0, 0.038624, 0, 236.0, 0.036161, 0, 237.0, 0.034053, 0, 238.0, 0.032227, 0, 239.0, 0.030633, 0, 240.0, 0.029227, 0, 241.0, 0.027981, 0, 242.0, 0.026867, 0, 243.0, 0.025867, 0, 244.0, 0.024963, 0, 245.0, 0.024144, 0, 246.0, 0.023398, 0, 247.0, 0.022716, 0, 248.0, 0.02209, 0, 249.0, 0.021514, 0, 250.0, 0.020983, 0, 251.0, 0.020491, 0, 252.0, 0.020035, 0, 253.0, 0.01961, 0, 254.0, 0.019215, 0, 255.0, 0.018846, 0, 256.0, 0.018502, 0, 257.0, 0.018179, 0, 258.0, 0.017876, 0, 259.0, 0.017592, 0, 260.0, 0.017324, 0, 261.0, 0.017072, 0, 262.0, 0.016835, 0, 263.0, 0.016612, 0, 264.0, 0.0164, 0, 265.0, 0.016201, 0, 266.0, 0.016012, 0, 267.0, 0.015834, 0, 268.0, 0.015665, 0, 269.0, 0.015505, 0, 270.0, 0.015353, 0, 271.0, 0.01521, 0, 272.0, 0.015074, 0, 273.0, 0.014945, 0, 274.0, 0.014823, 0, 275.0, 0.014707, 0, 276.0, 0.014597, 0, 277.0, 0.014493, 0, 278.0, 0.014395, 0, 279.0, 0.014301, 0, 280.0, 0.014213, 0, 281.0, 0.01413, 0, 282.0, 0.014051, 0, 283.0, 0.013976, 0, 284.0, 0.013906, 0, 285.0, 0.01384, 0, 286.0, 0.013778, 0, 287.0, 0.01372, 0, 288.0, 0.013665, 0, 289.0, 0.013615, 0, 290.0, 0.013567, 0, 291.0, 0.013523, 0, 292.0, 0.013482, 0, 293.0, 0.013445, 0, 294.0, 0.013411, 0, 295.0, 0.013379, 0, 296.0, 0.013351, 0, 297.0, 0.013326, 0, 298.0, 0.013304, 0, 299.0, 0.013284, 0, 300.0, 0.013268, 0, 301.0, 0.013254, 0, 302.0, 0.013243, 0, 303.0, 0.013235, 0, 304.0, 0.013229, 0, 305.0, 0.013227, 0, 306.0, 0.013227, 0, 307.0, 0.01323, 0, 308.0, 0.013235, 0, 309.0, 0.013243, 0, 310.0, 0.013254, 0, 311.0, 0.013268, 0, 312.0, 0.013285, 0, 313.0, 0.013304, 0, 314.0, 0.013327, 0, 315.0, 0.013352, 0, 316.0, 0.01338, 0, 317.0, 0.013412, 0, 318.0, 0.013446, 0, 319.0, 0.013483, 0, 320.0, 0.013524, 0, 321.0, 0.013568, 0, 322.0, 0.013615, 0, 323.0, 0.013666, 0, 324.0, 0.013721, 0, 325.0, 0.013779, 0, 326.0, 0.013841, 0, 327.0, 0.013906, 0, 328.0, 0.013977, 0, 329.0, 0.014051, 0, 330.0, 0.01413, 0, 331.0, 0.014213, 0, 332.0, 0.014301, 0, 333.0, 0.014395, 0, 334.0, 0.014494, 0, 335.0, 0.014598, 0, 336.0, 0.014708, 0, 337.0, 0.014825, 0, 338.0, 0.014948, 0, 339.0, 0.015078, 0, 340.0, 0.015216, 0, 341.0, 0.015361, 0, 342.0, 0.015515, 0, 343.0, 0.015678, 0, 344.0, 0.01585, 0, 345.0, 0.016033, 0, 346.0, 0.016227, 0, 347.0, 0.016432, 0, 348.0, 0.016651, 0, 349.0, 0.016883, 0, 350.0, 0.017131, 0, 351.0, 0.017395, 0, 352.0, 0.017677, 0, 353.0, 0.017979, 0, 354.0, 0.018302, 0, 355.0, 0.018649, 0, 356.0, 0.019022, 0, 357.0, 0.019425, 0, 358.0, 0.01986, 0, 359.0, 0.020332, 0, 360.0, 0.020845, 0, 361.0, 0.021405, 0, 362.0, 0.022018, 0, 363.0, 0.022691, 0, 364.0, 0.023435, 0, 365.0, 0.024259, 0, 366.0, 0.025179, 0, 367.0, 0.026211, 0, 368.0, 0.027377, 0, 369.0, 0.028704, 0, 370.0, 0.030229, 0, 371.0, 0.031997, 0, 372.0, 0.034074, 0, 373.0, 0.036545, 0, 374.0, 0.039537, 0, 375.0, 0.043231, 0, 376.0, 0.047908, 0, 377.0, 0.054019, 0, 378.0, 0.062344, 0, 379.0, 0.07435, 0, 380.0, 0.093175, 0, 381.0, 0.126927, 0, 382.0, 0.205035, 0, 383.0, 0.539199, 0, 384.0, 0.199932, 0, 385.0, 0.125326, 0, 386.0, 0.092591, 0, 387.0, 0.074202, 0, 388.0, 0.062425, 0, 389.0, 0.054237, 0, 390.0, 0.048216, 0, 391.0, 0.043601, 0, 392.0, 0.039953, 0, 393.0, 0.036997, 0, 394.0, 0.034554, 0, 395.0, 0.0325, 0, 396.0, 0.030751, 0, 397.0, 0.029243, 0, 398.0, 0.02793, 0, 399.0, 0.026776, 0, 400.0, 0.025756, 0, 401.0, 0.024846, 0, 402.0, 0.024031, 0, 403.0, 0.023296, 0, 404.0, 0.022631, 0, 405.0, 0.022026, 0, 406.0, 0.021473, 0, 407.0, 0.020967, 0, 408.0, 0.020502, 0, 409.0, 0.020073, 0, 410.0, 0.019676, 0, 411.0, 0.019309, 0, 412.0, 0.018967, 0, 413.0, 0.01865, 0, 414.0, 0.018354, 0, 415.0, 0.018077, 0, 416.0, 0.017818, 0, 417.0, 0.017576, 0, 418.0, 0.017348, 0, 419.0, 0.017135, 0, 420.0, 0.016934, 0, 421.0, 0.016745, 0, 422.0, 0.016567, 0, 423.0, 0.016399, 0, 424.0, 0.016241, 0, 425.0, 0.016091, 0, 426.0, 0.01595, 0, 427.0, 0.015817, 0, 428.0, 0.015691, 0, 429.0, 0.015572, 0, 430.0, 0.01546, 0, 431.0, 0.015354, 0, 432.0, 0.015254, 0, 433.0, 0.015159, 0, 434.0, 0.01507, 0, 435.0, 0.014985, 0, 436.0, 0.014906, 0, 437.0, 0.014831, 0, 438.0, 0.01476, 0, 439.0, 0.014694, 0, 440.0, 0.014632, 0, 441.0, 0.014573, 0, 442.0, 0.014519, 0, 443.0, 0.014468, 0, 444.0, 0.01442, 0, 445.0, 0.014376, 0, 446.0, 0.014336, 0, 447.0, 0.014298, 0, 448.0, 0.014264, 0, 449.0, 0.014233, 0, 450.0, 0.014204, 0, 451.0, 0.014179, 0, 452.0, 0.014156, 0, 453.0, 0.014137, 0, 454.0, 0.01412, 0, 455.0, 0.014106, 0, 456.0, 0.014094, 0, 457.0, 0.014085, 0, 458.0, 0.014079, 0, 459.0, 0.014075, 0, 460.0, 0.014074, 0, 461.0, 0.014075, 0, 462.0, 0.014079, 0, 463.0, 0.014086, 0, 464.0, 0.014095, 0, 465.0, 0.014107, 0, 466.0, 0.014121, 0, 467.0, 0.014138, 0, 468.0, 0.014157, 0, 469.0, 0.014179, 0, 470.0, 0.014204, 0, 471.0, 0.014231, 0, 472.0, 0.014261, 0, 473.0, 0.014294, 0, 474.0, 0.014329, 0, 475.0, 0.014368, 0, 476.0, 0.014409, 0, 477.0, 0.014453, 0, 478.0, 0.0145, 0, 479.0, 0.01455, 0, 480.0, 0.014603, 0, 481.0, 0.01466, 0, 482.0, 0.014719, 0, 483.0, 0.014782, 0, 484.0, 0.014849, 0, 485.0, 0.014919, 0, 486.0, 0.014992, 0, 487.0, 0.01507, 0, 488.0, 0.015151, 0, 489.0, 0.015237, 0, 490.0, 0.015327, 0, 491.0, 0.015421, 0, 492.0, 0.015519, 0, 493.0, 0.015623, 0, 494.0, 0.015731, 0, 495.0, 0.015845, 0, 496.0, 0.015963, 0, 497.0, 0.016088, 0, 498.0, 0.016218, 0, 499.0, 0.016355, 0, 500.0, 0.016498, 0, 501.0, 0.016648, 0, 502.0, 0.016805, 0, 503.0, 0.016969, 0, 504.0, 0.017142, 0, 505.0, 0.017323, 0, 506.0, 0.017513, 0, 507.0, 0.017713, 0, 508.0, 0.017922, 0, 509.0, 0.018143, 0, 510.0, 0.018374, 0, 511.0, 0.018618, 0, 512.0, 0.018875, 0, 513.0, 0.019146, 0, 514.0, 0.019432, 0, 515.0, 0.019734, 0, 516.0, 0.020053, 0, 517.0, 0.020392, 0, 518.0, 0.02075, 0, 519.0, 0.02113, 0, 520.0, 0.021535, 0, 521.0, 0.021965, 0, 522.0, 0.022424, 0, 523.0, 0.022914, 0, 524.0, 0.023439, 0, 525.0, 0.024001, 0, 526.0, 0.024606, 0, 527.0, 0.025257, 0, 528.0, 0.02596, 0, 529.0, 0.026722, 0, 530.0, 0.027549, 0, 531.0, 0.028451, 0, 532.0, 0.029436, 0, 533.0, 0.030519, 0, 534.0, 0.031713, 0, 535.0, 0.033036, 0, 536.0, 0.03451, 0, 537.0, 0.036161, 0, 538.0, 0.038024, 0, 539.0, 0.040141, 0, 540.0, 0.042569, 0, 541.0, 0.045379, 0, 542.0, 0.048669, 0, 543.0, 0.052573, 0, 544.0, 0.05728, 0, 545.0, 0.063065, 0, 546.0, 0.070344, 0, 547.0, 0.079781, 0, 548.0, 0.092499, 0, 549.0, 0.110567, 0, 550.0, 0.138255, 0, 551.0, 0.186025, 0, 552.0, 0.288136, 0, 553.0, 0.659499, 0, 554.0, 0.366392, 0, 555.0, 0.214689, 0, 556.0, 0.152852, 0, 557.0, 0.119272, 0, 558.0, 0.09818, 0, 559.0, 0.083701, 0, 560.0, 0.073144, 0, 561.0, 0.065106, 0, 562.0, 0.05878, 0, 563.0, 0.053671, 0, 564.0, 0.049458, 0, 565.0, 0.045925, 0, 566.0, 0.042918, 0, 567.0, 0.040329, 0, 568.0, 0.038075, 0, 569.0, 0.036095, 0, 570.0, 0.034343, 0, 571.0, 0.03278, 0, 572.0, 0.031377, 0, 573.0, 0.030112, 0, 574.0, 0.028964, 0, 575.0, 0.027918, 0, 576.0, 0.026962, 0, 577.0, 0.026083, 0, 578.0, 0.025273, 0, 579.0, 0.024524, 0, 580.0, 0.023829, 0, 581.0, 0.023183, 0, 582.0, 0.022581, 0, 583.0, 0.022018, 0, 584.0, 0.021491, 0, 585.0, 0.020996, 0, 586.0, 0.020531, 0, 587.0, 0.020092, 0, 588.0, 0.019679, 0, 589.0, 0.019288, 0, 590.0, 0.018918, 0, 591.0, 0.018567, 0, 592.0, 0.018234, 0, 593.0, 0.017917, 0, 594.0, 0.017616, 0, 595.0, 0.017329, 0, 596.0, 0.017056, 0, 597.0, 0.016795, 0, 598.0, 0.016545, 0, 599.0, 0.016307, 0, 600.0, 0.016078, 0, 601.0, 0.01586, 0, 602.0, 0.01565, 0, 603.0, 0.015449, 0, 604.0, 0.015256, 0, 605.0, 0.015071, 0, 606.0, 0.014893, 0, 607.0, 0.014722, 0, 608.0, 0.014557, 0, 609.0, 0.014399, 0, 610.0, 0.014246, 0, 611.0, 0.014099, 0, 612.0, 0.013958, 0, 613.0, 0.013822, 0, 614.0, 0.01369, 0, 615.0, 0.013564, 0, 616.0, 0.013442, 0, 617.0, 0.013324, 0, 618.0, 0.01321, 0, 619.0, 0.013101, 0, 620.0, 0.012995, 0, 621.0, 0.012894, 0, 622.0, 0.012795, 0, 623.0, 0.012701, 0, 624.0, 0.01261, 0, 625.0, 0.012522, 0, 626.0, 0.012437, 0, 627.0, 0.012356, 0, 628.0, 0.012277, 0, 629.0, 0.012202, 0, 630.0, 0.01213, 0, 631.0, 0.01206, 0, 632.0, 0.011994, 0, 633.0, 0.01193, 0, 634.0, 0.011869, 0, 635.0, 0.011811, 0, 636.0, 0.011755, 0, 637.0, 0.011703, 0, 638.0, 0.011653, 0, 639.0, 0.011606, 0, 640.0, 0.011561, 0, 641.0, 0.011519, 0, 642.0, 0.01148, 0, 643.0, 0.011444, 0, 644.0, 0.01141, 0, 645.0, 0.01138, 0, 646.0, 0.011352, 0, 647.0, 0.011328, 0, 648.0, 0.011306, 0, 649.0, 0.011287, 0, 650.0, 0.011272, 0, 651.0, 0.01126, 0, 652.0, 0.011252, 0, 653.0, 0.011247, 0, 654.0, 0.011246, 0, 655.0, 0.01125, 0, 656.0, 0.011257, 0, 657.0, 0.011269, 0, 658.0, 0.011285, 0, 659.0, 0.011307, 0, 660.0, 0.011334, 0, 661.0, 0.011367, 0, 662.0, 0.011407, 0, 663.0, 0.011453, 0, 664.0, 0.011507, 0, 665.0, 0.011569, 0, 666.0, 0.01164, 0, 667.0, 0.011721, 0, 668.0, 0.011814, 0, 669.0, 0.011919, 0, 670.0, 0.012038, 0, 671.0, 0.012173, 0, 672.0, 0.012327, 0, 673.0, 0.012501, 0, 674.0, 0.0127, 0, 675.0, 0.012928, 0, 676.0, 0.01319, 0, 677.0, 0.013492, 0, 678.0, 0.013844, 0, 679.0, 0.014256, 0, 680.0, 0.014743, 0, 681.0, 0.015327, 0, 682.0, 0.016034, 0, 683.0, 0.016907, 0, 684.0, 0.018008, 0, 685.0, 0.019435, 0, 686.0, 0.02135, 0, 687.0, 0.024047, 0, 688.0, 0.028116, 0, 689.0, 0.034937, 0, 690.0, 0.048681, 0, 691.0, 0.090547, 0, 692.0, 0.088697, 0, 693.0, 0.048016, 0, 694.0, 0.034421, 0, 695.0, 0.027608, 0, 696.0, 0.023508, 0, 697.0, 0.020766, 0, 698.0, 0.018799, 0, 699.0, 0.017318, 0, 700.0, 0.016161, 0, 701.0, 0.015231, 0, 702.0, 0.014465, 0, 703.0, 0.013823, 0, 704.0, 0.013277, 0, 705.0, 0.012806, 0, 706.0, 0.012395, 0, 707.0, 0.012033, 0, 708.0, 0.011711, 0, 709.0, 0.011423, 0, 710.0, 0.011164, 0, 711.0, 0.010929, 0, 712.0, 0.010714, 0, 713.0, 0.010518, 0, 714.0, 0.010338, 0, 715.0, 0.010171, 0, 716.0, 0.010017, 0, 717.0, 0.009873, 0, 718.0, 0.009739, 0, 719.0, 0.009614, 0, 720.0, 0.009497, 0, 721.0, 0.009387, 0, 722.0, 0.009284, 0, 723.0, 0.009186, 0, 724.0, 0.009094, 0, 725.0, 0.009006, 0, 726.0, 0.008924, 0, 727.0, 0.008845, 0, 728.0, 0.008771, 0, 729.0, 0.0087, 0, 730.0, 0.008633, 0, 731.0, 0.008569, 0, 732.0, 0.008507, 0, 733.0, 0.008449, 0, 734.0, 0.008394, 0, 735.0, 0.00834, 0, 736.0, 0.00829, 0, 737.0, 0.008241, 0, 738.0, 0.008195, 0, 739.0, 0.008151, 0, 740.0, 0.008109, 0, 741.0, 0.008068, 0, 742.0, 0.00803, 0, 743.0, 0.007993, 0, 744.0, 0.007958, 0, 745.0, 0.007925, 0, 746.0, 0.007893, 0, 747.0, 0.007863, 0, 748.0, 0.007834, 0, 749.0, 0.007807, 0, 750.0, 0.007781, 0, 751.0, 0.007757, 0, 752.0, 0.007734, 0, 753.0, 0.007713, 0, 754.0, 0.007692, 0, 755.0, 0.007674, 0, 756.0, 0.007656, 0, 757.0, 0.00764, 0, 758.0, 0.007625, 0, 759.0, 0.007611, 0, 760.0, 0.007599, 0, 761.0, 0.007588, 0, 762.0, 0.007578, 0, 763.0, 0.007569, 0, 764.0, 0.007562, 0, 765.0, 0.007556, 0, 766.0, 0.007552, 0, 767.0, 0.007549, 0, 768.0, 0.007547, 0, 769.0, 0.007547, 0, 770.0, 0.007548, 0, 771.0, 0.00755, 0, 772.0, 0.007554, 0, 773.0, 0.00756, 0, 774.0, 0.007567, 0, 775.0, 0.007575, 0, 776.0, 0.007585, 0, 777.0, 0.007597, 0, 778.0, 0.007611, 0, 779.0, 0.007626, 0, 780.0, 0.007643, 0, 781.0, 0.007662, 0, 782.0, 0.007684, 0, 783.0, 0.007707, 0, 784.0, 0.007732, 0, 785.0, 0.00776, 0, 786.0, 0.007789, 0, 787.0, 0.007822, 0, 788.0, 0.007857, 0, 789.0, 0.007894, 0, 790.0, 0.007934, 0, 791.0, 0.007978, 0, 792.0, 0.008024, 0, 793.0, 0.008074, 0, 794.0, 0.008127, 0, 795.0, 0.008184, 0, 796.0, 0.008245, 0, 797.0, 0.00831, 0, 798.0, 0.008379, 0, 799.0, 0.008453, 0, 800.0, 0.008533, 0, 801.0, 0.008617, 0, 802.0, 0.008708, 0, 803.0, 0.008805, 0, 804.0, 0.008908, 0, 805.0, 0.009019, 0, 806.0, 0.009138, 0, 807.0, 0.009265, 0, 808.0, 0.009402, 0, 809.0, 0.009549, 0, 810.0, 0.009707, 0, 811.0, 0.009878, 0, 812.0, 0.010062, 0, 813.0, 0.010261, 0, 814.0, 0.010477, 0, 815.0, 0.010712, 0, 816.0, 0.010967, 0, 817.0, 0.011246, 0, 818.0, 0.011552, 0, 819.0, 0.011888, 0, 820.0, 0.012258, 0, 821.0, 0.012669, 0, 822.0, 0.013125, 0, 823.0, 0.013636, 0, 824.0, 0.01421, 0, 825.0, 0.014859, 0, 826.0, 0.0156, 0, 827.0, 0.016452, 0, 828.0, 0.017441, 0, 829.0, 0.018602, 0, 830.0, 0.019983, 0, 831.0, 0.021652, 0, 832.0, 0.023708, 0, 833.0, 0.026301, 0, 834.0, 0.029669, 0, 835.0, 0.034219, 0, 836.0, 0.040699, 0, 837.0, 0.050659, 0, 838.0, 0.067916, 0, 839.0, 0.105086, 0, 840.0, 0.243423, 0, 841.0, 0.20222, 0, 842.0, 0.095752, 0, 843.0, 0.063075, 0, 844.0, 0.047209, 0, 845.0, 0.037831, 0, 846.0, 0.031632, 0, 847.0, 0.027228, 0, 848.0, 0.023936, 0, 849.0, 0.02138, 0, 850.0, 0.019337, 0, 851.0, 0.017666, 0, 852.0, 0.016273, 0, 853.0, 0.015093, 0, 854.0, 0.01408, 0, 855.0, 0.0132, 0, 856.0, 0.012429, 0, 857.0, 0.011747, 0, 858.0, 0.011139, 0, 859.0, 0.010593, 0, 860.0, 0.0101, 0, 861.0, 0.009653, 0, 862.0, 0.009245, 0, 863.0, 0.00887, 0, 864.0, 0.008526, 0, 865.0, 0.008208, 0, 866.0, 0.007913, 0, 867.0, 0.007638, 0, 868.0, 0.007382, 0, 869.0, 0.007142, 0, 870.0, 0.006918, 0, 871.0, 0.006706, 0, 872.0, 0.006507, 0, 873.0, 0.006319, 0, 874.0, 0.00614, 0, 875.0, 0.005971, 0, 876.0, 0.005811, 0, 877.0, 0.005658, 0, 878.0, 0.005512, 0, 879.0, 0.005373, 0, 880.0, 0.00524, 0, 881.0, 0.005113, 0, 882.0, 0.004991, 0, 883.0, 0.004874, 0, 884.0, 0.004762, 0, 885.0, 0.004653, 0, 886.0, 0.004549, 0, 887.0, 0.004448, 0, 888.0, 0.004351, 0, 889.0, 0.004258, 0, 890.0, 0.004167, 0, 891.0, 0.004079, 0, 892.0, 0.003994, 0, 893.0, 0.003912, 0, 894.0, 0.003832, 0, 895.0, 0.003754, 0, 896.0, 0.003679, 0, 897.0, 0.003606, 0, 898.0, 0.003534, 0, 899.0, 0.003465, 0, 900.0, 0.003397, 0, 901.0, 0.003331, 0, 902.0, 0.003267, 0, 903.0, 0.003204, 0, 904.0, 0.003143, 0, 905.0, 0.003083, 0, 906.0, 0.003024, 0, 907.0, 0.002967, 0, 908.0, 0.002911, 0, 909.0, 0.002856, 0, 910.0, 0.002802, 0, 911.0, 0.00275, 0, 912.0, 0.002698, 0, 913.0, 0.002647, 0, 914.0, 0.002598, 0, 915.0, 0.002549, 0, 916.0, 0.002501, 0, 917.0, 0.002454, 0, 918.0, 0.002408, 0, 919.0, 0.002363, 0, 920.0, 0.002318, 0, 921.0, 0.002274, 0, 922.0, 0.002231, 0, 923.0, 0.002189, 0, 924.0, 0.002147, 0, 925.0, 0.002106, 0, 926.0, 0.002065, 0, 927.0, 0.002025, 0, 928.0, 0.001986, 0, 929.0, 0.001947, 0, 930.0, 0.001909, 0, 931.0, 0.001871, 0, 932.0, 0.001834, 0, 933.0, 0.001797, 0, 934.0, 0.001761, 0, 935.0, 0.001725, 0, 936.0, 0.00169, 0, 937.0, 0.001655, 0, 938.0, 0.001621, 0, 939.0, 0.001587, 0, 940.0, 0.001553, 0, 941.0, 0.00152, 0, 942.0, 0.001487, 0, 943.0, 0.001454, 0, 944.0, 0.001422, 0, 945.0, 0.001391, 0, 946.0, 0.001359, 0, 947.0, 0.001328, 0, 948.0, 0.001297, 0, 949.0, 0.001267, 0, 950.0, 0.001237, 0, 951.0, 0.001207, 0, 952.0, 0.001177, 0, 953.0, 0.001148, 0, 954.0, 0.001119, 0, 955.0, 0.00109, 0, 956.0, 0.001062, 0, 957.0, 0.001033, 0, 958.0, 0.001005, 0, 959.0, 0.000978, 0, 960.0, 0.00095, 0, 961.0, 0.000923, 0, 962.0, 0.000896, 0, 963.0, 0.000869, 0, 964.0, 0.000843, 0, 965.0, 0.000816, 0, 966.0, 0.00079, 0, 967.0, 0.000764, 0, 968.0, 0.000738, 0, 969.0, 0.000713, 0, 970.0, 0.000687, 0, 971.0, 0.000662, 0, 972.0, 0.000637, 0, 973.0, 0.000612, 0, 974.0, 0.000588, 0, 975.0, 0.000563, 0, 976.0, 0.000539, 0, 977.0, 0.000515, 0, 978.0, 0.000491, 0, 979.0, 0.000467, 0, 980.0, 0.000444, 0, 981.0, 0.00042, 0, 982.0, 0.000397, 0, 983.0, 0.000374, 0, 984.0, 0.000351, 0, 985.0, 0.000328, 0, 986.0, 0.000305, 0, 987.0, 0.000282, 0, 988.0, 0.00026, 0, 989.0, 0.000238, 0, 990.0, 0.000215, 0, 991.0, 0.000193, 0, 992.0, 0.000171, 0, 993.0, 0.00015, 0, 994.0, 0.000128, 0, 995.0, 0.000106, 0, 996.0, 0.000085, 0, 997.0, 0.000063, 0, 998.0, 0.000042, 0, 999.0, 0.000021, 0, 1000.0, 0.0, 0, 1000.0, 0.033681, 0 ],
					"id" : "obj-12",
					"maxclass" : "function",
					"numinlets" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "float", "", "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 136.0, 581.0, 200.0, 100.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-11",
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 136.0, 224.0, 20.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-9",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 3,
					"outlettype" : [ "bang", "bang", "int" ],
					"patching_rect" : [ 136.0, 272.0, 56.0, 20.0 ],
					"text" : "uzi 1000"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-8",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "bang", "dump" ],
					"patching_rect" : [ 136.0, 56.0, 57.0, 20.0 ],
					"text" : "t b dump"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-7",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 136.0, 32.0, 41.0, 18.0 ],
					"text" : "dump"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-5",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 344.666656, 247.0, 83.0, 20.0 ],
					"text" : "zl 2000 group"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-4",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 256.666656, 247.0, 83.0, 20.0 ],
					"text" : "zl 2000 group"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-3",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "float" ],
					"patching_rect" : [ 256.666656, 215.0, 76.0, 20.0 ],
					"text" : "unpack 0. 0."
				}

			}
, 			{
				"box" : 				{
					"addpoints" : [ 0.0, 0.0, 2, 95.744682, 0.666667, 2, 223.404251, 0.973333, 0, 382.978729, 0.56, 2, 553.191467, 0.88, 0, 691.48938, 0.173333, 2, 840.425537, 0.573333, 0, 1000.0, 0.0, 2 ],
					"id" : "obj-2",
					"maxclass" : "function",
					"numinlets" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "float", "", "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 136.0, 96.0, 200.0, 100.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-52",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 367.75, 333.0, 50.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-51",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 445.0, 333.0, 50.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-50",
					"maxclass" : "newobj",
					"numinlets" : 5,
					"numoutlets" : 1,
					"outlettype" : [ "FullPacket" ],
					"patching_rect" : [ 136.0, 385.0, 328.0, 20.0 ],
					"text" : "o.pack /x 0. /xx 0. 0.25 0.75 1. /yy 0. 0.5 0.5 0. /a 1. /w0 500"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-1",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 136.0, 425.0, 89.0, 20.0 ],
					"text" : "o.simple-interp"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-13", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-17", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-11", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-15", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-13", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-14", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-14", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-15", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-15", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-16", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-50", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-16", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-18", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-3", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-2", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-50", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-20", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-28", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-4", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-3", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-5", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-3", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-50", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-4", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-50", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-5", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-50", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-50", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-51", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-50", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-52", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-7", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-4", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-5", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-16", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-9", 2 ]
				}

			}
 ],
		"dependency_cache" : [ 			{
				"name" : "o.simple-interp.maxpat",
				"bootpath" : "/Users/john/Development/cnmat/trunk/max/externals/odot/trunk/testing",
				"patcherrelativepath" : "",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "o.let.maxpat",
				"bootpath" : "/Users/john/MMJ5-dev/odot-darwin-1.0b/abstractions",
				"patcherrelativepath" : "../../../../../../../../MMJ5-dev/odot-darwin-1.0b/abstractions",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "o.union.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "o.pak.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "o.expr.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "o.if.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "o.var.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "o.route.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "o.atomize.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "o.message.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "o.pack.mxo",
				"type" : "iLaX"
			}
 ]
	}

}
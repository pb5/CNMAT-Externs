{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 142.0, 44.0, 1208.0, 760.0 ],
		"bglocked" : 0,
		"defrect" : [ 142.0, 44.0, 1208.0, 760.0 ],
		"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
		"openinpresentation" : 0,
		"default_fontsize" : 20.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 0,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 0,
		"toolbarvisible" : 1,
		"boxanimatetime" : 200,
		"imprint" : 0,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"boxes" : [ 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "tracing",
					"patching_rect" : [ 924.0, 783.0, 150.0, 29.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-31",
					"fontsize" : 20.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"patching_rect" : [ 868.0, 775.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-25",
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "o.build /a 1 5 7 4 /verbose 1",
					"patching_rect" : [ 867.0, 816.0, 257.0, 29.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-27",
					"fontsize" : 20.0,
					"outlettype" : [ "FullPacket" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"patching_rect" : [ 689.0, 771.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-23",
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "o.build /a 1 5 7 4",
					"patching_rect" : [ 688.0, 812.0, 158.0, 29.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-21",
					"fontsize" : 20.0,
					"outlettype" : [ "FullPacket" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "o.message",
					"text" : "/n 6.5 \n/n/factorial 1055.742188 \n",
					"linecount" : 2,
					"patching_rect" : [ 40.973145, 796.0, 290.0, 48.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-14",
					"fontsize" : 18.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "o.route /n/n",
					"patching_rect" : [ 39.0, 750.0, 112.0, 29.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"numoutlets" : 2,
					"id" : "obj-11",
					"fontsize" : 20.0,
					"outlettype" : [ "", "FullPacket" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "o.expr /n/factorial = 1 /n/n= /n",
					"patching_rect" : [ 42.0, 615.0, 245.0, 27.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-4",
					"fontsize" : 18.0,
					"outlettype" : [ "FullPacket" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "o.expr /n/factorial *= /n/n--",
					"patching_rect" : [ 138.973145, 702.0, 218.0, 27.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-7",
					"fontsize" : 18.0,
					"outlettype" : [ "FullPacket" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "o.if !(/n/n > 0)",
					"patching_rect" : [ 40.973137, 664.0, 117.0, 27.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"numoutlets" : 2,
					"id" : "obj-8",
					"fontsize" : 18.0,
					"outlettype" : [ "FullPacket", "FullPacket" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"patching_rect" : [ 596.0, 765.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-50",
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "o.expr /a=4",
					"patching_rect" : [ 557.0, 821.0, 111.0, 29.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-48",
					"fontsize" : 20.0,
					"outlettype" : [ "FullPacket" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "You can signal the OSC address to compute from using an abstraction to wrap the core recursion like this:",
					"linecount" : 3,
					"patching_rect" : [ 642.0, 678.0, 380.0, 75.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-47",
					"fontsize" : 20.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "We can create a temporary variable so\nas to leave /n untouched:\n",
					"linecount" : 2,
					"patching_rect" : [ 7.0, 551.0, 555.0, 52.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-45",
					"fontsize" : 20.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "o.message",
					"text" : "/a 1 5 7 4 \n/a/factorial 1 120 5040 24 \n",
					"linecount" : 2,
					"patching_rect" : [ 614.973145, 906.0, 553.0, 48.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-43",
					"fontsize" : 18.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "o.factorial /a",
					"patching_rect" : [ 557.0, 859.0, 119.0, 29.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-42",
					"fontsize" : 20.0,
					"outlettype" : [ "FullPacket" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "20.",
					"patching_rect" : [ 384.0, 169.0, 36.0, 25.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-41",
					"fontsize" : 18.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "20",
					"patching_rect" : [ 185.0, 129.0, 31.0, 25.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-40",
					"fontsize" : 18.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "15",
					"patching_rect" : [ 386.0, 137.0, 31.0, 25.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-39",
					"fontsize" : 18.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "10",
					"patching_rect" : [ 347.0, 122.0, 31.0, 25.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-38",
					"fontsize" : 18.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "edge case values",
					"linecount" : 2,
					"patching_rect" : [ 246.0, 164.0, 138.0, 48.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-37",
					"fontsize" : 18.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "regular case",
					"patching_rect" : [ 5.0, 61.0, 137.0, 27.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-35",
					"fontsize" : 18.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "edge case types",
					"linecount" : 2,
					"patching_rect" : [ 197.0, 14.0, 138.0, 48.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-34",
					"fontsize" : 18.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "4 7 2",
					"patching_rect" : [ 270.0, 58.0, 51.0, 25.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-32",
					"fontsize" : 18.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "6.",
					"patching_rect" : [ 157.0, 28.0, 32.0, 25.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-29",
					"fontsize" : 18.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "fred",
					"patching_rect" : [ 162.0, 63.0, 42.0, 25.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-28",
					"fontsize" : 18.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "6.5",
					"patching_rect" : [ 221.0, 57.0, 36.0, 25.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-26",
					"fontsize" : 18.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "-2",
					"patching_rect" : [ 310.0, 124.0, 32.0, 25.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-24",
					"fontsize" : 18.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "0",
					"patching_rect" : [ 270.0, 123.0, 31.0, 25.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-22",
					"fontsize" : 18.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "o.message",
					"text" : "/n -0.5 \n/n/factorial 1055.742188 \n",
					"linecount" : 3,
					"patching_rect" : [ 40.973145, 408.0, 157.0, 69.0 ],
					"textcolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-19",
					"fontsize" : 18.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "1",
					"patching_rect" : [ 230.0, 123.0, 31.0, 25.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-17",
					"fontsize" : 18.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "o.expr /n/factorial = 1",
					"patching_rect" : [ 88.0, 250.0, 179.0, 27.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-16",
					"fontsize" : 18.0,
					"outlettype" : [ "FullPacket" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "OSC messages without /n or outside numerical bounds are passed through.\n\n",
					"linecount" : 5,
					"patching_rect" : [ 398.0, 230.0, 188.0, 110.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-15",
					"fontsize" : 18.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "This tutorial illustrates some classical defensive programming practices with o. using the factorial function as an example.\n\nAdrian Freed 2011 ",
					"linecount" : 5,
					"patching_rect" : [ 467.0, 11.0, 405.0, 110.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-12",
					"fontsize" : 18.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "4",
					"patching_rect" : [ 25.0, 113.0, 31.0, 25.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-10",
					"fontsize" : 18.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "5",
					"patching_rect" : [ 61.0, 100.0, 31.0, 25.0 ],
					"fontname" : "Arial",
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-6",
					"fontsize" : 18.0,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "o.expr /n/factorial *= /n--",
					"patching_rect" : [ 163.973145, 335.0, 204.0, 27.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-3",
					"fontsize" : 18.0,
					"outlettype" : [ "FullPacket" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "o.if !(/n > 0)",
					"patching_rect" : [ 86.973137, 299.0, 102.0, 27.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"numoutlets" : 2,
					"id" : "obj-2",
					"fontsize" : 18.0,
					"outlettype" : [ "FullPacket", "FullPacket" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "o.build /n 1",
					"patching_rect" : [ 84.973137, 180.0, 100.0, 27.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-1",
					"fontsize" : 18.0,
					"outlettype" : [ "FullPacket" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "                 The core recursion\n\n\n\n\n\n\n\n",
					"linecount" : 8,
					"patching_rect" : [ 48.0, 217.0, 349.0, 172.0 ],
					"fontname" : "Arial",
					"numinlets" : 1,
					"bgcolor" : [ 0.011765, 1.0, 0.803922, 1.0 ],
					"numoutlets" : 0,
					"id" : "obj-13",
					"fontsize" : 18.0
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-41", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-40", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-39", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-38", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-32", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-28", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-24", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-22", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-16", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-6", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-2", 0 ],
					"destination" : [ "obj-19", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 0 ],
					"destination" : [ "obj-2", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-2", 1 ],
					"destination" : [ "obj-3", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 0 ],
					"destination" : [ "obj-2", 0 ],
					"hidden" : 0,
					"midpoints" : [ 173.473145, 380.0, 378.986572, 380.0, 378.986572, 290.0, 96.473137, 290.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"midpoints" : [ 148.473145, 745.0, 418.986572, 745.0, 418.986572, 655.0, 50.473137, 655.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 1 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 0 ],
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-11", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 1 ],
					"destination" : [ "obj-14", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-50", 0 ],
					"destination" : [ "obj-48", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-4", 0 ],
					"hidden" : 0,
					"midpoints" : [ 94.473137, 211.0, 20.0, 211.0, 29.0, 557.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 0 ],
					"destination" : [ "obj-21", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-25", 0 ],
					"destination" : [ "obj-27", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 0 ],
					"destination" : [ "obj-42", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 0 ],
					"destination" : [ "obj-42", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-42", 0 ],
					"destination" : [ "obj-43", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-48", 0 ],
					"destination" : [ "obj-42", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}

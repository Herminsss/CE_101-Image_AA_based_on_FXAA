#include <wx/image.h>
#include <vector>

using namespace std;
//-------------------------------------------------------------------
//Math function recreations for doubles
//-------------------------------------------------------------------

double dmax (double a, double b)
{
	double max;
	max = b > a ? b : a;
	return max;
}

double dmin (double a, double b)
{
	double min;
	min = b < a ? b : a; 
	return min;
}

double dabs (double a)
{
	double abs;
	abs = a > 0 ? a : -a;
	return abs;
}

//---------------------------------------------------------------------
//Main program
//---------------------------------------------------------------------

//Store Image as 3D vector (width, height, RGB)
	
std::vector< vector< vector< unsigned char > > > 
						retrieveImageColor (wxImage image)
{
	std::vector< vector< vector< unsigned char > > > color;
	int width, height;
	unsigned char red, green, blue;
	
	height = image.GetHeight();
	width = image.GetWidth();
	
	for (int y = 0; y < height; y++)
	{
		
		color.push_back(vector< vector< unsigned char > >());
		
		for (int x = 0; x < width; x++)
		{
			color[y].push_back(vector< unsigned char >());
            
            red = image.GetRed(x, y);
			green = image.GetGreen(x, y);
			blue = image.GetBlue(x, y);
			
			color[y][x].push_back(red);
			color[y][x].push_back(green);
			color[y][x].push_back(blue);
		}
	}
	
	return color;
}

//Convert 3D vector of colors (width, height, RGB) to Image

wxImage outputImage (std::vector< vector< vector< unsigned char > > > color)
{
	int height, width;
	unsigned char red, green, blue;
	
	height = color.size();
	width = color[0].size();
	
	wxImage Image = wxImage(width, height);
	
	for (int y = 0; y < height; y++)
	{	
		for (int x = 0; x < width; x++)
		{
			red = color[y][x][0];
			green = color[y][x][1];
			blue = color[y][x][2];
			
			Image.SetRGB(x, y, red, green, blue);
		}
	}
	
	return Image;
}

//--------------------------------------------------------------------

//Compute for the luma values of all pixels in the image

std::vector< vector< double > > convertColortoLuma
			(std::vector< vector< vector < unsigned char > > > color)
{
	std::vector< vector< double > > luma;
	double currLuma;
	int height, width;
	
	height = color.size();
	width = color[0].size();
	
	for (int y = 0; y < height; y++)
	{
		luma.push_back(vector< double >());
		
		for (int x = 0; x < width; x++)
		{
			currLuma = 	(double) color[y][x][0] / 255 * 0.2126 
						+ (double) color[y][x][1] / 255 * 0.7152
						+ (double) color[y][x][2] / 255 * 0.0722;
			luma[y].push_back(currLuma);
		}
	}
	
	return luma;
}

//Determine whether current edge pixel is Horizontal or Vertical

bool classifyEdgeHorizontal(std::vector< vector< double > > luma, int y, int x)
{
	bool isHorizontal;
	double edgeHorizontal, edgeVertical;
	
	edgeHorizontal = 	dabs(-2.0 * luma[y][x-1] + luma[y-1][x-1] + luma[y+1][x-1])  
						+ dabs(-2.0 * luma[y][x] + luma[y-1][x] + luma[y+1][x]) * 2.0    
						+ dabs(-2.0 * luma[y][x+1] + luma[y-1][x+1] + luma[y+1][x+1]);
	edgeVertical = 	dabs(-2.0 * luma[y-1][x] + luma[y-1][x-1] + luma[y-1][x+1]) 
					+ dabs(-2.0 * luma[y][x] + luma[y][x-1] + luma[y][x+1]) * 2.0  
					+ dabs(-2.0 * luma[y+1][x] + luma[y+1][x-1] + luma[y+1][x+1]);
					
	isHorizontal = edgeHorizontal > edgeVertical;
	return isHorizontal;
}

//Main function for antialiasing logic, takes inputs and outputs of
//images in 3D vector format (width, height, RGB)

std::vector< vector< vector< unsigned char > > > antiAlias 
	(	std::vector< vector< vector< unsigned char > > > color,
		double edgeThreshold, 
		double edgeThresholdMin
	)
{
	std::vector< vector< vector< unsigned char > > > aaColor;
	std::vector< vector< double > > luma; 
	double rangeMin, rangeMax, range;
	double edgeHorizontal, edgeVertical;
	int height, width;
	bool isHorizontal;
	
	height = color.size();
	width = color[0].size();
	
	luma = convertColortoLuma(color);
	
	for (int y = 1; y < height-1; y++)
	{
		aaColor.push_back(vector< vector< unsigned char > >());
		for (int x = 1; x < width-1; x++)
		{
			rangeMin = dmin(luma[y][x], dmin(dmin(luma[y-1][x], luma[y][x-1]), dmin(luma[y+1][x], luma[y][x+1])));
			rangeMax = dmax(luma[y][x], dmax(dmax(luma[y-1][x], luma[y][x-1]), dmax(luma[y+1][x], luma[y][x+1])));
			
			range = rangeMax - rangeMin;				
				
			if (range < edgeThresholdMin || 
				range < edgeThreshold * rangeMax)
			{
				aaColor[y].push_back(color[y][x]);
			}
			
			// Is the local edge horizontal or vertical ?
			isHorizontal = classifyEdgeHorizontal(luma, y, x);
			
			if (isHorizontal)
			{
		    aaColor[y].push_back(vector< unsigned char >());
				aaColor[y][x].push_back(0);
				aaColor[y][x].push_back(0);
				aaColor[y][x].push_back(255);
			}
			else
			{
		    aaColor[y].push_back(vector< unsigned char >());
				aaColor[y][x].push_back(0);
				aaColor[y][x].push_back(255);
				aaColor[y][x].push_back(255);
			} 
//			for(uint i = 0; i < FXAA_SEARCH_STEPS; i++) 
//			{
//				#if FXAA_SEARCH_ACCELERATION == 1
//				{	
//					if(!doneN) lumaEndN = FxaaLuma(FxaaTexture(tex, posN.xy).xyz);
//					if(!doneP) lumaEndP = FxaaLuma(FxaaTexture(tex, posP.xy).xyz);
//				}
//				#else
//				{
//					if(!doneN) lumaEndN = FxaaLuma(FxaaTextureGrad(tex, posN.xy, offNP).xyz);
//					if(!doneP) lumaEndP = FxaaLuma(FxaaTextureGrad(tex, posP.xy, offNP).xyz);
//				}
//				#endif
//				doneN = doneN || (abs(lumaEndN - lumaN) >= gradientN);
//				doneP = doneP || (abs(lumaEndP - lumaN) >= gradientN);
//				if(doneN && doneP) break;
//				if(!doneN) posN -= offNP;
//				if(!doneP) posP += offNP;
//			}
			
		}
	}
	
	return aaColor;
} 

//-------------------------------------------------------------------

//Invokable external function for antialiasing
//Includes the conversions to and from 3D vector format and wxImages 

wxImage antiAliasImage  ( wxImage inputImage,
                          double edgeThreshold, 
  		                    double edgeThresholdMin
                        )
{
	wxImage outImg;
	vector< vector< vector< unsigned char > > > color;
	vector< vector< vector< unsigned char > > > outColor;
	
	color = retrieveImageColor(inputImage);
	outColor = 	antiAlias 	(color, edgeThreshold, edgeThresholdMin);
	outImg = outputImage(outColor);
	return outImg;
}

/*

config variables from FXAA whitepaper

FXAA_EDGE_THRESHOLD
The minimum amount of local contrast required to apply algorithm.
1/3 – too little
1/4 – low quality
1/8 – high quality
1/16 – overkill

FXAA_EDGE_THRESHOLD_MIN
Trims the algorithm from processing darks.
1/32 – visible limit
1/16 – high quality
1/12 – upper limit (start of visible unfiltered edges)

*/

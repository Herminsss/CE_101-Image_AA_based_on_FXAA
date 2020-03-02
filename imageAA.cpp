#include <wx/bitmap.h>
#include <wx/image.h>
#include <vector>

//-------------------------------------------------------------------
//Math function recreations for doubles
//-------------------------------------------------------------------

private double dmax (double a, double b)
{
	double max;
	max = b > a ? b : a;
	return max;
}

private double dmin (double a, double b)
{
	double min;
	min = b < a ? b : a; 
	return min;
}

private double dabs (double a)
{
	double abs;
	abs = a > 0 ? a : -a;
	return abs;
}

//---------------------------------------------------------------------
//Main program
//---------------------------------------------------------------------

//Store Image as 3D vector (width, height, RGB)
	
private std::vector< vector< vector< unsigned char > > > 
						retrieveImageColor (wxImage image)
{
	std::vector< vector< vector< unsigned char > > > color;
	int width, height;
	unsigned char red, green, blue;
	
	height = image.GetHeight();
	width = image.GetWidth();
	
	for (int y = 0; y < height; y++)
	{
		retrieveColor.pushback();
		
		for (int x = 0; x < width; x++)
		{
			red = image.GetRed(x, y);
			green = image.GetGreen(x, y);
			blue = image.GetBlue(x, y);
			
			color[y].push_back({red, green, blue});
		}
	}
	
	return color;
}

//Convert 3D vector of colors (width, height, RGB) to Image

private wxImage outputImage (std::vector< vector< vector< unsigned char > > > color)
{
	int height, width;
	unsigned char red, green, blue;
	
	height = color.size();
	width = color[0].size();
	
	Image = wxImage(width, height);
	
	for (int y = 0; y < height; y++)
	{
		retrieveColor.pushback();
		
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

private std::vector< vector< double > > convertColortoLuma
			(std::vector< vector< vector < unsigned char > > > color)
{
	std::vector< vector<unsigned char> > luma;
	unsigned char currLuma;
	
	height = color.size();
	width = color[0].size();
	
	for (int y = 0; y < height; y++)
	{
		luma.pushback();
		
		for (int x = 0; x < width; x++)
		{
			currLuma = 	(double) color[y][x][0] / 255 * 0.2126 
						+ color[y][x][1] /255 * 0.7152
						+ color[y][x][2] /255 * 0.0722;
			luma.pushback[y]](currLuma);
		}
	}
	
	return luma;
}

//Determine whether current edge pixel is Horizontal or Vertical

private bool classifyEdgeHorizontal(std::vector< vector< double > > luma, int y, int x)
{
	bool isHorizontal;
	double edgeHorizontal, edgeVertical;
	
	edgeHorizontal = 	dabs(-2.0 * luma[y][x-1] + luma[y-1][x-1] + luma[y+1][x-1])  
						+ dabs(-2.0 * luma[y][x] + luma[y-1][x] + luma[y+1][x]) * 2.0    
						+ dabs(-2.0 * luma[y][x+1] + luma[y-1][x+1] + luma[y+1][x+1]);
	edgeVertical = 	dabs(-2.0 * luma[y-1][x] + luma[y-1][x-1] + luma[y-1][x+1]) 
					+ dabs(-2.0 * luma[y][x] + luma[y][x-1] + luma[y][x+1]) * 2.0  
					+ dabs(-2.0 * luma[y+1][x] + luma[y+1][x-1] + luma[y+1][x+1]);
					
	isHorizontal = edgeHorizontal > edgeVertical ? True : False;
	return isHorizontal
}

//Main function for antialiasing logic, takes inputs and outputs of
//images in 3D vector format (width, height, RGB)

private std::vector< vector< vector< unsigned char > > > antiAlias 
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
	
	luma = convertColortoLuma(color)
	
	for (int y = 1; y < height-1; y++)
	{
		aaColor.pushback();
		
		for (int x = 1; x < width-1; x++)
		{
			rangeMin = dmin(luma[y][x], dmin(dmin(luma[y-1][x], luma[y][x-1]), dmin(luma[y+1][x], luma[y][x+1])));
			rangeMax = dmax(luma[y][x], dmax(dmax(luma[y-1][x], luma[y][x-1]), dmax(luma[y+1][x], luma[y][x+1])));
			
			range = rangeMax - rangeMin;				
				
			if (range < edgeThresholdMin || 
				range < edgeThreshold * rangeMax)
			{
				aaColor[y].pushback(color[y][x]);
			}
			
			// Is the local edge horizontal or vertical ?
			isHorizontal = classifyEdgeHorizontal(luma, y, x);
			
			
		}
	}
	
	return aaColor;
} 

//-------------------------------------------------------------------

//Invokable external function for antialiasing
//Includes the conversions to and from 3D vector format and wxImages 

public wxImage antiAliasImage (wxImage inputImage){
	wxImage outImg;
	std::vector< vector< vector< unsigned char > > > color;
	std::vector< vector< vector< unsigned char > > > outColor;
	
	color = retrieveImageColor(image);
	outColor = 	antiAlias 	(	std::vector< vector< vector< unsigned char > > > color,
								double edgeThreshold, 
								double edgeThresholdMin
							);
	outImg = outputImage(outColor);
	return outImg;
}

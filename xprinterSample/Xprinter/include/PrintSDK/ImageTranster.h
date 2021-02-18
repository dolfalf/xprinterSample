#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


@interface ImageTranster : NSObject

typedef enum {
    Dithering=0,    //Picture monochrome processing method: binary method
    Threshold       //Dithering algorithm
} BmpType;

typedef enum {
    RasterNolmorWH=0,   //Mode of printing raster bitmap: normal size
    RasterDoubleWidth,  //Double width
    RasterDoubleHeight, //Double height
    RasterDoubleWH      //Double width and height
} PrintRasterType;



+(NSData *)Imagedata:(UIImage *) mImage andType:(BmpType) bmptype andPaperHeight:(int)paperheight;

+(NSData *)rasterImagedata:(UIImage *) mIamge andType:(BmpType) bmptype andPrintRasterType:(PrintRasterType) type andPaperHeight:(int)paperheight;


@end


//
//  MWIFIManager.h
//  Printer
//
//  Created by apple on 16/4/5.
//  Copyright © 2016年 Admin. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
@class MWIFIManager;
typedef void(^MWIFIBlock)(BOOL isConnect);
typedef void(^MWIFICallBackBlock)(NSData *data);
enum {
    SocketOfflineByServer,  // The server is offline, the default is 0
    SocketOfflineByUser,    // User actively cut
};

/**
  *Connect multiple devices
  * Use MWIFIManager *manager = [[MWIFIManager alloc] init] to instantiate objects,
  * Save the manager, and specify the corresponding manager when sending the command to send the command
  */
@protocol MWIFIManagerDelegate <NSObject>

// successfully connected to the host
-(void)MWIFIManager:(MWIFIManager *)manager didConnectedToHost:(NSString *)host port:(UInt16)port;
// Disconnect
-(void)MWIFIManager:(MWIFIManager *)manager willDisconnectWithError:(NSError *)error;
// write data successfully
-(void)MWIFIManager:(MWIFIManager *)manager didWriteDataWithTag:(long)tag;
// Received postback
-(void)MWIFIManager:(MWIFIManager *)manager didReadData:(NSData *)data tag:(long)tag;
// Disconnect
-(void)MWIFIManagerDidDisconnected:(MWIFIManager *)manager;
@end

@interface MWIFIManager : NSObject
{
    int commandSendMode; //Command sending mode 0: send immediately 1: batch send
}
#pragma mark-Basic attributes
// host address
@property (nonatomic,copy) NSString *hostStr;
// port
@property (nonatomic,assign) UInt16 port;
// Whether the connection is successful
@property (nonatomic,assign) BOOL connectOK;
// Is it automatically disconnected or manually disconnected
@property (nonatomic,assign) BOOL isAutoDisconnect;

@property (nonatomic,weak) id<MWIFIManagerDelegate> delegate;
// Connection callback
@property (nonatomic,copy) MWIFIBlock callBack;
// Receive the data returned by the server
@property (nonatomic,copy) MWIFICallBackBlock callBackBlock;
@property (nonatomic,strong) NSMutableArray *commandBuffer;
//Send queue array
#pragma mark-Basic method
+ (instancetype)shareWifiManager;
//Connect to the host
-(void)MConnectWithHost:(NSString *)hostStr port:(UInt16)port completion:(MWIFIBlock)block;
// Disconnect the host
-(void)MDisConnect;
//Recommended for the modified version to use two methods of sending data
-(void)MWriteCommandWithData:(NSData *)data;
-(void)MWriteCommandWithData:(NSData *)data withResponse:(MWIFICallBackBlock)block;
// Send TSC complete instructions
-(void)MSendMSGWith:(NSString *)str;

// Send M complete instruction
//- (void)MWriteMCommandWithData:(NSData *)data withResponse:(MWIFICallBackBlock)block;
//#pragma mark-printer command
//#pragma mark-====================TSC instruction===================
///**
// * 1. Set label size
// * width: label width
// * height: label height
// */
//- (void)MaddSizeWidth:(int)width height:(int)height;
///**
// * 2. Set the gap length
// * gap: gap length
// */
//- (void)MaddGap:(int)gap;
///**
// * 3. Generate cash drawer control pulse
// * m: cash drawer pin number
// * t1: high level time
// * t2: low level time
// */
//- (void)MaddCashDrwer:(int)m t1:(int)t1 t2:(int)t2;
///**
// * 4. Control the stop position of each label
// * offset: stop offset
// */
//- (void)MaddOffset:(float)offset;
///**
// * 5. Set printing speed
// * speed: printing speed
// */
//- (void)MaddSpeed:(float)speed;
///**
// * 6. Set the print density
// * n: print density
// */
//- (void)MaddDensity:(int)n;
///**
// * 7. Set printing direction and mirror image
// * n: printing direction
// */
//- (void)MaddDirection:(int)n;
///**
// * 8. Set the origin coordinate
// * x: abscissa of origin
// * y: ordinate of origin
// */
//- (void)MaddReference:(int)x y:(int)y;
///**
// * 9. Clear print buffer data
// */
//- (void)MaddCls;
///**
// * 10. Paper feed
// * feed: paper length
// */
//- (void)MaddFeed:(int)feed;
///**
// * 11. Unload the paper
// * feed: the length of unloaded paper
// */
//- (void)MaddBackFeed:(int)feed;
///**
// * 12. Take a piece of label paper distance
// */
//- (void)MaddFormFeed;
///**
// * 13. The label position is calibrated once
// */
//- (void)MaddHome;
///**
// * 14.Print label
// * m: number of labels printed
// */
//- (void)MaddPrint:(int)m;
///**
// * 15. Set the international code page
// * page: International code page
// */
//- (void)MaddCodePage:(int)page;
///**
// * 16.Set the buzzer
// * level: sound level
// * interval: the length of the sound
// */
//- (void)MaddSound:(int)level interval:(int)interval;
///**
// * 17. Set the printer to report an error
// * feed: paper length
// */
//- (void)MaddLimitFeed:(int)feed;
///**
// * 18.Draw black blocks in the print buffer
// * x: Actually the abscissa
// * y: starting ordinate
// * width: line width
// * height: line height
// */
//- (void)MaddBar:(int)x y:(int)y width:(int)width height:(int)height;
///**
// * 19. Draw a one-dimensional barcode in the print buffer
// * x: Actually the abscissa
// * y: starting ordinate
// * type: barcode type
// * height: barcode height
// * readable: whether to print identifiable characters
// * rotation: barcode rotation angle 0,90,180,270
// * conten: Bar code data, the data needs to refer to the bar code rules to input
// */
//- (void)Madd1DBarcodeX:(int)x
// y:(int)y
// type:(NSString *)type
// height:(int)height
// readable:(int)readable
// rotation:(int)rotation
// narrow:(int)narrow
// wide:(int)wide
// content:(NSString *)content;
///**
// * 20. Draw a rectangle in the print buffer
// * x: Actually the abscissa
// * y: starting ordinate
// * xend: the abscissa of the end point
// * yend: the ordinate of the end point
// */
//- (void)MaddBox:(int)x y:(int)y xend:(int)xend yend:(int)yend;
///**
// * 21. Draw a bitmap in the print buffer
// * x: starting abscissa
// * y: starting ordinate
// * width: bitmap printing width
// * height: height
// */
//- (void)MaddBitmap:(int)x
// y:(int)y
// width:(int)width
// height:(int)height
// mode:(int)mode data:(int)data;
///**
// * 22. Erase the data in the specified area in the print buffer
// * x: starting abscissa
// * y: starting ordinate
// * xwidth: horizontal width
// * yheight: vertical height
// */
//- (void)MaddErase:(int)x y:(int)y xwidth:(int)xwidth yheight:(int)yheight;
///**
// * 23. Invert the black and white data of the specified area
// * x: starting abscissa
// * y: starting ordinate
// * xwidth: horizontal width
// * yheight: vertical height
// */
//- (void)MaddReverse:(int)x y:(int)y xwidth:(int)xwidth yheight:(int)yheight;
///**
// * 24. Draw text in the print buffer
// * x: starting abscissa
// * y: starting ordinate
// * font: font type
// * rotation: rotation angle
// * xmul: horizontal magnification factor 1-10 times
// * ymul: vertical magnification factor 1-10 times
// * content: text string
// */
//- (void)MaddText:(int)x y:(int)y font:(NSString *)font rotation:(int)rotation x_mul:(int)xmul y_mul:(int)ymul content:(NSString *)content;
///**
// * 25. Draw text in the print buffer
// * x: starting abscissa
// * y: starting ordinate
// * level: error correction level
// * cellWidth: cell size
// * totation: rotation angle
// * dataStr: print text
// */
//- (void)MaddQRCode:(int)x y:(int)y level:(int)level cellWidth:(int)cellWidth rotation:(int)totation data:(NSString *)dataStr;
///**
// * 26. Set whether the stripping function is turned on
// * enable: whether to enable
// */
//- (void)MaddPeel:(NSString *)enable;
///**
// * 27. Set whether the tear-off function is enabled
// * enable: whether to enable
// */
//- (void)MaddTear:(NSString *)enable;
//
///**
// * 28. Set whether the cutter function is turned on
// * enable: whether to enable
// */
//- (void)MaddCut:(NSString *)enable;
///**
// * 29. When setting the printer error, whether to print the previous content
// * enable: whether to enable
// */
//- (void)MaddReprint:(NSString *)enable;
///**
// * 30. Set whether to press the paper feed button to print the latest label
// * enable: whether to enable
// */
//- (void)MaddPrintKeyEnable:(NSString *)enable;
///**
// * 31. Set the number of copies of the latest label printed by pressing the paper feed key
// * m: number of prints
// */
//- (void)MaddPrintKeyNum:(int)m;
//
//
//#pragma mark-================ M instruction===================
///**
// *1. Horizontal positioning
// */
//- (void)MhorizontalMition;
///**
// * 2. Print and wrap
// */
//- (void)MprintAndFeed;
///**
// * 3. Print and return to standard mode
// */
//- (void)MPrintAndBackToNormalModel;
///**
// * 4. Cancel printing data in page mode
// */
//- (void)MCancelPrintData;
///**
// * 5. Real-time status transmission
// * param: specify the printing status to be transmitted
// * 1 <= param <= 4
// * callBlock: related status returned by the printer
// */
//- (void)MUpdataPrinterState:(int)param completion:(MWIFICallBackBlock)callBlock;
///**
// * 6. Real-time request to the printer
// * param: indicates the request sent to the printer
// * 1 <= param <= 2
// */
//- (void)MUpdataPrinterAnswer:(int)param;
///**
// * 7. Generate cash drawer opening pulse in real time
// * m: Specify the pin of the cash drawer socket
// * t: level time
// * n = 1
// * m = 0,1
// * 1 <= t <= 8
// */
//- (void)MOpenBoxAndPulse:(int) n m:(int) m t:(int) t;
///**
// * 8. Print in page mode
// */
//- (void)MPrintOnPageModel;
///**
// * 9. Set the right spacing of characters
// * n: represents the character spacing
// * 0 <= n <= 255
// */
//- (void)MSetCharRightMargin:(int)n;
///**
// * 10. Select print mode
// * n: Set the character printing mode according to the value of n
// * 0 <= n <= 255
// */
//- (void)MSelectPrintModel:(int)n;
///**
// * 11.Set the absolute printing position
// * 0 <= nL <= 255
// * 0 <= nh <= 255
// */
//- (void)MSetPrintLocationWithParam:(int)nL nH:(int)nH;
///**
// * 12. Select/cancel user-defined characters
// * 0 <= n <= 255
// */
//- (void)MSelectOrCancelCustomCharacter:(int)n;
//
///**
// * 13.Define user-defined characters
// * y=3
// * 32<=c1<=c2<=127
// * 0<=x<=12 ​​Standard ASCII code font A (12 x 24)
// * 0<=x<=9 Compressed SCII code font (9 x 17)
// * 0<=d1 ... d(y*xk)<=255
// * points: point matrix array, array element bit string type
// */
//- (void)MDefinCustomCharacter:(int)y c1:(int)c1 c2:(int)c2 dx:(NSArray *)points;
///**
// * 14.Select bitmap mode
// * Select a bitmap mode specified by m, the number of bitmap points is determined by nL and nH
// * m=0,1,32,33
// * 0<=nL<=255
// * 0<=nH<=3
// * 0<=d<=255
// */
//- (void)MSelectBitmapModel:(int)m nL:(int)nL nH:(int)nH dx:(NSArray *)points;
//
///**
// * 15. Cancel the underline mode
// * 0<=n<=2,48<=n<=50
// * Select or cancel the underline mode according to the value of n
// */
//- (void)MCancelUnderLineModelWith:(int)n;
///**
// * 16.Set the default line spacing
// */
//- (void)MSetDefaultLineMargin;
///**
// * 17. Set line spacing
// * 0<=n<=255
// * Set line spacing [n* vertical or horizontal movement unit]
// */
//- (void)MSetLineMarginWith:(int)n;
///**
// * 18.Select printer
// * 0<=n<=1
// */
//- (void)MSelectPrinterWith:(int)n;
///**
// * 19. Cancel user-defined characters
// * 32<=n<=127
// */
//- (void)MCancelCustomCharacterWith:(int)n;
///**
// * 20. Initialize the printer
// *
// */
//- (void)MInitializePrinter;
///**
// * 21. Set the horizontal tab position
// * 1<=n<=255
// * 0<=k<=32
// */
//- (void)MSetTabLocationWith:(NSArray *)points;
///**
// * 22. Select/cancel bold mode
// * 0<=n<=255
// * When the lowest bit of n is 0, the bold mode is cancelled, when the bit is 1, the bold mode is selected
// */
//- (void)MSelectOrCancelBoldModelWith:(int)n;
///**
// * 23. Select/cancel double printing mode
// * 0<=n<=255
// * The lowest bit of n: 0 cancel
// * 1 bold
// */
//- (void)MSelectOrCancelDoublePrintModel:(int)n;
///**
// * 24. Print and feed paper
// * 0<=n<=255
// * Print buffer data and feed paper [n*Vertical or horizontal movement unit]
// */
//- (void)MPrintAndPushPageWith:(int)n;
///**
// * 25. Select page mode
// */
//- (void)MSelectPageModel;
///**
// * 26. Choose font
// * n = 0,1,48,49
// */
//- (void)MSelectFontWith:(int)n;
///**
// * 27. Choose an international character set
// * 0<=n<=15
// */
//- (void)MSelectINTL_CHAR_SETWith:(int)n;
///**
// * 28. Select standard mode
// */
//- (void)MSelectNormalModel;
///**
// * 29. Select the print area direction in page mode
// * 0<=n<=3 48<=n<=51
// * n specifies the direction and starting position of the print area
// */
//- (void)MSelectPrintDirectionOnPageModel:(int)n;
///**
// * 30. Select/Cancel rotate 90 degrees clockwise
// * 0<=n<=1 48<=n<=49
// * 0,48: cancel
// * 1,49: select
// */
//- (void)MSelectOrCancelRotationClockwise:(int)n;
///**
// * 31. Set print area in page mode
// * Range: 0<=xL,xH,yL,yH,dxL,dxH,dyL,dyH<=255
// */
//- (void)MSetprintLocationOnPageModelWithXL:(int)xL
// xH:(int)xH
// yL:(int)yL
// yH:(int)yH
// dxL:(int)dxL
// dxH:(int)dxH
// dyL:(int)dyL
// dyH:(int)dyH;
//
///**
// * 32. Set the horizontal printing position
// * Range: nL 0-255
// nH 0-255
// */
//- (void)MSetHorizonLocationWith:(int)nL nH:(int)nH;
///**
// * 33. Choose alignment
// * Range: n 0-2
// 48-50
// */
//- (void)MSelectAlignmentWithN:(int)n;
///**
// * 34. Select paper sensor to output signal
// * Range: n 0-255
// */
//- (void)MSelectSensorForOutputSignal:(int)n;
///**
// * 35. Select the paper sensor to stop printing
// * Range: n 0-255
// */
//- (void)MSelectSensorForStopPrint:(int)n;
///**
// * 36. Allow/Prohibit keys
// * Range: n 0-255
// */
//- (void)MAllowOrDisableKeypress:(int)n;
///**
// * 37. Print and feed the paper forward N lines
// * Range: n 0-255
// */
//- (void)MPrintAndPushPageRow:(int)n;
///**
// * 38. Generate cash drawer control pulse
// * Range: m 0, 1, 48, 49
// t1 0-255
// t2 0-255
// */
//- (void)MMakePulseWithCashboxWithM:(int)m t1:(int)t1 t2:(int)t2;
///**
// * 39. Select the character code table
// * Range: n 0-10 or 16-19
// */
//- (void)MSelectCharacterTabN:(int)n;
///**
// * 40. Select/cancel upside down printing mode
// * Range: n 0-255
// */
//- (void)MSelectOrCancelInversionPrintModel:(int)n;
///**
// * 41. Print the bitmap downloaded to FLASH
// * Range: n 1-255
// m 0-3, 48-51
// */
//- (void)MPrintFlashBitmapWithN:(int)n m:(int)m;
///**
// * 42. Define FLASH bitmap
// *Range: n 1-255
// * points: the horizontal and vertical points of the bitmap
// */
//- (void)MDefinFlashBitmapWithN:(int)n Points:(NSArray *)points;
///**
// * 43. Choose character size
// * Range: n 0-255
// */
//- (void)MSelectCharacterSize:(int)n;
///**
// * 44. Set the vertical absolute position in page mode
// * Range: nL 1-255
// nH 0-255
// */
//- (void)MSetVertLocationOnPageModelWithnL:(int)nL nH:(int)nH;
///**
// * 45. Define download bitmap
// * Range: x 1-255
// y 1-48
// x * y <= 912
// d 0-255
// */
//- (void)MDefineLoadBitmapWithX:(int)x Y:(int)y Points:(NSArray *)points;
///**
// * 46. Perform hexadecimal dump of print data
// * Range: pL = 2
// pH = 0
// n = 0,48
// m = 1,49
// */
//- (void)MPrintDataAndSaveAsHexWithpL:(int)pL pH:(int)pH n:(int)n m:(int)m;
///**
// * 47. Print and download bitmap
// * Range: m 0-3 or 48-51
// */
//- (void)MPrintLoadBitmapM:(int)m;
///**
// * 48. Start/end macro definition
// */
//- (void)MBeginOrEndDefine;
///**
// * 49. Select/cancel black and white reverse printing mode
// * Range: n 0-255
// */
//- (void)MSelectORCancelBWPrintModel:(int)n;
///**
// * 50. Select the printing position of HRI characters
// * Range: n 0-3 or 48-51
// */
//- (void)MSelectHRIPrintLocation:(int)n;
///**
// * 51. Set the left margin
// * Range: nL 0-255
// nH 0-255
// */
//- (void)MSetLeftMarginWithnL:(int)nL nH:(int)nH;
///**
// * 52. Set horizontal and vertical movement units
// * Range: x 0-255
// y 0-255
// */
//- (void)MSetHoriAndVertUnitXWith:(int)x y:(int)y;
///**
// * 53. Select the cutting mode and cut the paper
// * model: 0,1 select mode 1 and mode 2
// * Mode 1 range: m = 0,48,1,49
// * Mode 2 range: m = 66, n = 0-255
// */
//- (void)MSelectCutPaperModelAndCutPaperWith:(int)m n:(int)n selectedModel:(int)model;
///**
// * 54. Set the width and height of the print area
// * Range: nL 0-255
// nH 0-255
// */
//- (void)MSetPrintLocationWith:(int)nL nH:(int)nH;
///**
// * 55. Set the vertical relative position in page mode
// * Range: nL 0-255
// nH 0-255
// */
//- (void)MSetVertRelativeLocationOnPageModelWith:(int)nL nH:(int)nH;
///**
// * 56. Execute macro commands
// * Range: r 0-255
// t 0-255
// m 0,1
// */
//- (void)MRunMacroMommandWith:(int)r t:(int)t m:(int)m;
///**
// * 57. Turn on/off the automatic status return function (ASB)
// * Range: n 0-255
// */
//- (void)MOpenOrCloseASB:(int)n;
///**
// * 58. Choose HRI to use font
// * Range: n 0,1,48,49
// */
//- (void)MSelectHRIFontToUse:(int)n;
///**
// * 59. Choose barcode height
// * Range: n 1-255
// */
//- (void)MSelectBarcodeHeight:(int)n;
///**
// * 60. Print barcode
// * model: 0,1 represents two types 0: represents type 1 1: represents type 2
// * Type 1: m 0-6
// * Type 2: m 65-73
// */
//- (void)MPrintBarCodeWithPoints:(int)m n:(int)n points:(NSArray *)points selectModel:(int)model;
///**
// * 61. Return status
// * Range: n 1,2,49,50
// */
//- (void)MCallBackStatus:(int)n completion:(MWIFICallBackBlock)block;
///**
// * 62. Print raster bitmap
// * Range: m 0-3 or 48-51
// xL 0-255
// xH 0-255
// yL 0-255
// yH 0-255
// points represent bitmap data
// */
//- (void)MPrintRasterBitmapWith:(int)m
// xL:(int)xL
// xH:(int)xH
// yl:(int)yL
// yh:(int)yH
// points:(NSArray *)points;
///**
// * 63. Set the barcode width
// * Range: n 2-6
// */
//- (void)MSetBarcodeWidth:(int)n;
//#pragma mark-============Chinese character control command============
///**
// * 64. Set Chinese character mode
// * Range: n 0-255
// */
//- (void)MSetChineseCharacterModel:(int)n;
///**
// * 65. Select Chinese character mode
// */
//- (void)MSelectChineseCharacterModel;
///**
// * 66. Select/cancel Chinese character underline mode
// * Range: n 0-2 or 48-50
// */
//- (void)MSelectOrCancelChineseUderlineModel:(int)n;
///**
// * 67. Cancel Chinese character mode
// */
//- (void)MCancelChineseModel;
///**
// * 68. Define user-defined Chinese characters
// * c1, c2 represent character encoding
// * points represents the Hanzi matrix
// */
//- (void)MDefineCustomChinesePointsC1:(int)c1 c2:(int)c2 points:(NSArray *)points;
///**
// * 69. Set the left and right spacing of Chinese characters
// * Range: n1 0-255
// n2 0-255
// */
//- (void)MSetChineseMarginWithLeftN1:(int)n1 n2:(int)n2;
///**
// * 70. Select/cancel double height and width of Chinese characters
// * Range: n 0-255
// */
//- (void)MSelectOrCancelChineseHModelAndWModel:(int)n;
//#pragma mark-============Printer prompt command============
///**
// * 72. Buzzer prompt when the printer comes to print the order
// * Range: n 1-9
// t 1-9
// */
//- (void)MPrinterSound:(int)n t:(int)t;
///**
// * 73. The buzzer and warning light flashes when the printer comes to print the order
// * Range: m 1-20
// t 1-20
// n 0-3
// */
//- (void)MPrinterSoundAndAlarmLight:(int)m t:(int)t n:(int)n;

-(void)MSetCommandMode:(BOOL)Mode;

/*
 * 74. Set the printer to send command mode
 * Range: 0, 1
 ＊ 0: Send immediately
 ＊ 1: Batch sending
 */

-(NSArray*)MGetBuffer;
/*
 * 75. Return to the waiting queue for sending instructions
 */

-(void)MClearBuffer;
/*
 * 76. Empty the waiting queue for sending instructions
 */

-(void)MSendCommandBuffer;
/*
 * 77. Send instruction queue
 */


@end

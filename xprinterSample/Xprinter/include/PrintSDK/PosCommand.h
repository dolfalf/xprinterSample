//
//  MCommand.h
//  Printer
//
//  Created by LeeLee on 16/7/19.
//  Copyright © 2016年 Admin. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ImageTranster.h"

/**
 M Commandクラス、そのクラスメソッドを呼び出して送信用のNsdataタイプのデータを返します。このクラスはMプリンターにのみ適用可能です。
 */
@interface MCommand : NSObject

/**
 Horizontal positioning<br>
 HT<br>
 09<br>
 */
+(NSData *) horizontalMition;
/**
 Print and wrap<br>
 LF<br>
 0A<br>
 */
+(NSData *) printAndFeedLine;
/**
 Print and return to standard mode<br>
 FF<br>
 OC<br>
 */
+(NSData *) printAndBackStandardModel;
/**
 Print and tab<br>
 CR<br>
 0D<br>
 */
+(NSData *) printAndTabs;
/**
 Cancel printing data in page mode<br>
 CAN<br>
 18<br>
 */
+(NSData *) canclePrintDataByPageModel;
/**
 Real-time status transmission<br>
 DLE EOT n<br>
 10 04 n<br>
 (int) n: 1<=n<=4.<br>
 */
+(NSData *) sendRealTimeStatus:(int) n;
/**
 Real-time printer request<br>
 DLE ENQ n<br>
 10 05 n<br>
 (int) n: 1<=n<=2.<br>
 */
+(NSData *) requestRealTimeForPrint:(int) n;
/**
 Generate cash drawer pulse in real time<br>
 DLE DC4 n m t<br>
 10 14 01 m t<br>
 (int) m: m=0, or 1; <br>
 (int) t: 1<=t<=8.<br>
 */
+(NSData *) openCashBoxRealTimeWithM:(int) m andT:(int) t;
/**
 Print in page mode<br>
 ESC FF<br>
 1B 0C<br>
 This command is only valid in page mode<br>
 */
+(NSData *) printUnderPageModel;
/**
 Set character right spacing<br>
 1B 20 n<br>
 (int) n: 0~255,in dots.<br>
 */
+(NSData *) setCharRightSpace:(int) n;
/**
 Choose print mode<br>
 ESC !n<br>
 1B 21 n<br>
 (int) n: 0~255, only the last digit of n is valid, 0 means cancel, 1 means select.<br>
 */
+(NSData *) selectPrintModel:(int) n;
/**
 Set absolute print position<br>
   ESC $ nL nH<br>
   1B 24 nL nH<br>
   nL+nH*256 represents the distance from the beginning of the line<br>
 */
+(NSData *) setAbsolutePrintMitionWithNL:(int) nL andNH:(int) nH;
/**
 Select or cancel user-defined characters<br>
   ESC% n<br>
   1B 25 n<br>
   (int) n: 0~255, only the last digit of n is valid, 0 means cancel, 1 means select.<br>
 */
+(NSData *) selectOrCancleCustomChar:(int) n;
/**
  Define user-defined characters
  ESC * m nL nH d1 d2 ...dk<br>
  (int) c1: starting character code<br>
  (int) c2: termination character code, 32<=c1<=c2<=127<br>
  (Byte*) bytes: The binary data of the character downloaded by the character. <br>
  */
+(NSData *) defineUserDefinedCharactersWithM:(int) m andNL:(int) nL andNH:(int) nH andBytes:(Byte *) bytes;
/**
  Select bitmap mode<br>
  ESC * m nL nH d1 d2 ...dk<br>
  m range: 0, 1, 32, 33, representing the density of different points<br>
  nL range: 0-255<br>
  nH range: 0-3<br>
  b={d1,d2...dk}, when m=0,1, k=nL+256*nH; when m=32,33, k=(nL+256*nH)*3;d:0- 255;<br>
  */
+(NSData *) selectBmpModelWithM:(int) m andnL:(int) nL andnH:(int) nH andNSData:(NSData *) data;
/**
  Select or cancel the underline mode<br>
  ESC-n<br>
  1B 2D n<br>
  (int) n:0 or 48 cancel;1 or 49 select(by 1 dot);2 or 50 select (by 2 dots).<br>
  */
+(NSData *) selectOrCancleUnderLineModel:(int) n;
/**
 Set default line spacing<br>
 ESC 2<br>
 */
+(NSData *) setDefultLineSpace;
/**
 Set line spacing<br>
 ESC 3 n<br>
 1B 33 n<br>
 */
+(NSData *) setDefultLineSpace:(int) n;
/**
 Select printer<br>
 ESC = n<br>
 1B 3D n<br>
 n:0或1<br>
 */
+(NSData *) selectPrinter:(int) n;
/**
  Cancel user-defined characters<br>
  ESC? N<br>
  Cancel the character with code n in user-defined characters<br>
  n Range: 32-127<br>
  */
+(NSData *) cancleUserDefinedCharacters:(int) n;
/**
  Initialize the printer<br>
  ESC @<br>
  1B 40<br>
  */
+(NSData *) initializePrinter;
/**
  Set horizontal tab position<br>
  ESC D n1 ...nk NUL<br>
  data={n1...nk};k<=32; Tab distance=character width*k<br>
  Please refer to the programming manual for the n value and k value in the parameter data<br>
  */
+(NSData *) setHorizontalTabsMition:(NSData *) data;
/**
  Select or cancel bold mode<br>
  ESC E n<br>
  1B 45 n<br>
  (int) n: 0~255, only the last digit of n is valid, 0 means cancel, 1 means select.<br>
  */
+(NSData *) selectOrCancleBoldModel:(int) n;
/**
 Select or cancel the dual printing mode<br>
 ESC G n<br>
 1B 47 n<br>
 (int) n: 0~255, only the last digit of n is valid, 0 means cancel, 1 means select.<br>
 */
+(NSData *) selectOrCancleDoublePrintModel:(int) n;
/**
 Print and feed paper<br>
 ESC J n<br>
 1B 4A n<br>
 (int) n: specify the length(in inch) feeds.
 */
+(NSData *) printAdnFeed:(int) n;
/**
 Select page mode<br>
 ESC L<br>
 1B 4C<br>
 
 */
+(NSData *) selectPagemodel;
/**
 Choose font<br>
 ESC M n<br>
 1B 4D n<br>
 n range: 0, 1, 48, 49;<br>
 */
+(NSData *) selectFont:(int) n;
/**
 Select international character set<br>
 ESC R n<br>
 n:0-15, represents an international character set<br>
 1B 52 n<br>
 */
+(NSData *) selectInternationCharacterSets:(int) n;
/**
 Select standard mode<br>
 ESC S<br>
 1B 53<br>
 */
+(NSData *) selectStabdardModel;
/**
 Select the print area direction in page mode<br>
 ESC T n<br>
 1B 54 n<br>
 (int) n: 0<=n<=3 or 48<=n<=51; n specifies the direction and starting position of the printing area. <br>
 */
+(NSData *) selectPrintDirectionUnderPageModel:(int) n;
/**
 Select or cancel 90 degrees clockwise rotation<br>
 This command is only valid in page mode<br>
 ESC V n<br>
 1B 56 n<br>
 (int) n: n=0 or 48 means cancel; n=1 or 49 means select.<br>
 */
+(NSData *) selectOrCancleCW90:(int) n;
/**
 Set print area in page mode<br>
 ESC W xL xH yL yH dxL dxH dyL dyH<br>
 1B 57 xL xH yL yH dxL dxH dyL dyH<br>
 xL+xH*256 represents the starting position in the x direction<br>
 yL+yH*256 represents the starting position in the y direction<br>
 dxL+dxH*256 represents the width in the x direction<br>
 dyL+dyH*256 represents the height in the y direction<br>
 */
+(NSData *) setPrintAreaUnderPageModelWithxL:(int) xL
                                       andxH:(int) xH
                                       andyL:(int) yL
                                       andyH:(int) yH
                                      anddxL:(int) dxL
                                      anddxH:(int) dxH
                                      anddyL:(int) dyL
                                      anddyK:(int) dyH;
/**
 Set relative horizontal printing position<br>
 ESC \ nL nH<br>
 1B 5C nL nH<br>
 nL+nH*256 represents the size of the setting<br>
 */
+(NSData *) setRelativeHorizontalPrintMitionWithnL:(int) nL andnH:(int) nH;
/**
 Choose alignment<br>
 ESC a n<br>
 1B 61 n<br>
 */
+(NSData *) selectAlignment:(int) n;
/**
 Select printer sensor to output paper feed signal<br>
 ESC c 3 n<br>
 1B 63 33 n<br>
 (int) n:0~255.<br>
 */
+(NSData *) selectPrintTransducerOutPutPageOutSignal:(int) n;
/**
 Select printer sensor-stop printing<br>
 ESC c 4 n<br>
 1B 63 34 n<br>
 (int) n:0~255.<br>
 */
+(NSData *) selectPrintTransducerStopPrint:(int) n;
/**
 Allow or prohibit keystrokes<br>
 ESC c 5 n<br>
 1B 63 35 n<br>
 (int) n: The last bit of n determines, 1 is allowed, 0 is forbidden. <br>
 */
+(NSData *) allowOrForbidPressButton:(int) n;
/**
 Print and feed the paper n lines forward<br>
 ESC d n<br>
 1B 64 n<br>
 (int) n:0~255.<br>
 */
+(NSData *) printAndFeedForwardWhitN:(int) n;
/**
 Generate cash drawer control pulse<br>
 ESC p m t1 t2<br>
 1B 70 m t1 t2<br>
 (int) m: connection pin, 0 or 1 or 48 or 49.<br>
 t1 ,t2 :0~255.<br>
 */
+(NSData *) creatCashBoxContorPulseWithM:(int) m andT1:(int) t1 andT2:(int) t2;
/**
 Select character code table<br>
 ESC t n<br>
 1B 74 n<br>
 (int) n: 0~10 or 16~19<br>
 */
+(NSData *) selectCharacterCodePage:(int) n;
/**
 Select or cancel upside-down printing<br>
 ESC {n<br>
 1B 7B n<br>
 (int) n: The last digit of n is determined, 1 is selected, 0 is canceled. <br>
 */
+(NSData *) selectOrCancleConvertPrintModel:(int) n;
/**
 Print the bitmap downloaded to FLASH<br>
 FS p n m<br>
 (int) n: represents the image of the nth position in the FLASH cache<br>
 (int) m: The method of printing FLASH bitmap, 0~3 or 48~51, respectively representing normal, double width, double height, double width and height. <br>
 */
+(NSData *) printBmpInFLASHWithN:(int) n andM:(int) m;
/**
 Define FLASH bitmap<br>
 FS q n [xL xH yL yH d1...dk]...[xL xH yL yH d1...dk]<br>
 1C 71 n data<br>
 n: number of defined bitmaps<br>
 data=[xL xH yL yH d1...dk]...[xL xH yL yH d1...dk], representing the data of multiple bitmaps, each bitmap contains xL xH yL yH representing the image Data width and height<br>
 */
+(NSData *)definedFlashBmpWithN:(int)n andBmp:(UIImage *)image andBmpType:(BmpType) bmptype andPrintType:(PrintRasterType) type andPaperHeight:(int) paperheight;
/**
 Select character size<br>
 GS! N<br>
 (int) n:0~255, 0-3 bits of n set the character height, 4-7 bits set the character width. <br>
 */
+(NSData *) selectCharacterSize:(int) n;
/**
 Set absolute position in page mode<br>
 GS $ nL nH<br>
 1D 24 nL nH<br>
 nL ,nH range: 0~255, nL+nH*256 represents the position, the unit is inch<br>
 */
+(NSData *) setAbsoluteMitionUnderPageModelWithnL:(int) nL andnH:(int) nH;
/**
 Define download bitmap<br>
 GS x y[d1...d(8*M)]<br>
 1D 2A data<br>
 (UIImage*) image :image object<br>
 */
+(NSData *)definedDownLoadBmp:(UIImage *)image byType:(BmpType) bmptype andPaperHeight:(int) paperheight;
/**
 Perform a hexadecimal dump of printer data<br>
 GS (A pL pH n m<br>
 1D 28 41 02 00 00 01<br>
 */
+(NSData *) executePrintDataSavaByTeansformToHex;
/**
 Print download bitmap<br>
 GS / m<br>
 1D 2F m<br>
 (int) m: print mode, range: 0~3 or 48~51.<br>
 */
+(NSData *) printDownLoadBmp:(int) m;
/**
 Start or end macro definition<br>
 GS :<br>
 1D 3A<br>
 */
+(NSData *) startOrStopMacrodeFinition;
/**
 Select or cancel black and white reverse printing mode<br>
 GS B n<br>
 1D 42 n<br>
 (int) n: The last digit of n is 1, select, 0, cancel.<br>
 */
+(NSData *) selectOrCancleInvertPrintModel:(int) n;
/**
 Select the printing position of HRI characters<br>
 GS H n<br>
 1D 48 n<br>
 (int) n:0~3 or 48~51, representing the printing position of the character relative to the barcode. <br>
 */
+(NSData *) selectHRICharactersPrintMition:(int) n;

/**
 Set the left margin<br>
 GS L nL nH<br>
 1D 4C nL nH<br>
 (nL+nH*256)*horizontal movement unit, representing the set left margin, unit: inch.<br>
 */

+(NSData *) setLeftSpaceWithnL:(int) nL andnH:(int) nH;
/**
 Set horizontal and vertical movement units<br>
 GS P x y<br>
 1D 50 x y<br>
 (int) x: horizontal movement unit, 0~255.<br>
 (int) y: vertical movement unit, 0~255.<br>
 */

+(NSData *) setHorizontalAndVerticalMoveUnitWithX:(int) x andY:(int) y;
/**
 Select paper cutting mode and cut paper<br>
 GS V m<br>
 1D 56 m<br>
 (int) m:0 or 48, full cut; 1 or 49, half cut.<br>
 */

+(NSData *) selectCutPageModelAndCutpage:(int) m;

/**
 Select paper cutting mode and cut paper<br>
 GS V m n<br>
 1D 56 m n<br>
 (int) m: m=66.<br>
 (int) n: Feed paper n, then half cut the paper. <br>
  */

+(NSData *) selectCutPageModelAndCutpageWithM:(int) m andN:(int) n;
/**
 Set print area width<br>
 GS W nL nH<br>
 1D 57 nL nH<br>
 (nL+nH*256)*Horizontal movement unit, representing the width of the printing area.<br>
 */
+(NSData *) setPrintAreaWidthWithnL:(int) nL andnH:(int) nH;
/**
 Set absolute print position in page mode<br>
 GS \ nL nH<br>
 1D 5C nL nH<br>
 (nL+nH*256)*Vertical movement unit, which represents the vertical movement distance relative to the current printing position.<br>
 */
+(NSData *) setVertivalRelativeMitionUnderPageModelWithNL:(int) nL andNH:(int) nH;
/**
 Execute macro command<br>
 GS ^ r t m<br>
 1D 5E r t m<br>
 (int) r:0~255, number of executions.<br>
 (int) t:0~255, execution waiting time. <br>
 (int) m:0 or 1, execution mode. <br>
 */
+(NSData *) executeMacrodeCommandWithR:(int) r andT:(int) t andM:(int) m;
/**
 Turn on or off the automatic status return function<br>
 GS a n<br>
 1D 61 n<br>
 (int) n: 0~255, each bit of n represents a different type of status return.<br>
 */
+(NSData *) openOrCloseAutoReturnPrintState:(int) n;
/**
 Choose HRI to use fonts<br>
 GS f n<br>
 1D 66 n<br>
 (int) n: 0 or 48 means standard; 1 or 49 means compressed font. <br>
 
 */
+(NSData *) selectHRIFont:(int) n;
/**
 Choose barcode height<br>
 GS h n<br>
 1D 68 n<br>
 (int) n: 1~255,defualt:162.<br>
 */
+(NSData *) setBarcodeHeight:(int) n;
/**
 Print barcode<br>
 GS k m d1...dk NUL<br>
 1D 6B m d1...dk 00<br>
 (int) m: Barcode type, 0~6.<br>
 (NSString*) content: Barcode content. <br>
 
 */
+(NSData *) printBarcodeWithM:(int) m andContent:(NSString *) content useEnCodeing:(NSStringEncoding) strEncoding;

/**
 Print barcode<br>
 GS k m n d1...dk<br>
 1D 6B m n d1...dk<br>
 (int) m: Barcode type, 66~73.<br>
 (int) n: The length of the barcode content. <br>
 */
+(NSData *) printBarcodeWithM:(int)m andN:(int) n andContent:(NSString *)content useEnCodeing:(NSStringEncoding) strEncoding;
/**
 Return status<br>
 GS r n<br>
 1D 72 n<br>
 (int) n: 1,2,49,50; 1 or 49 returns the sensor status, 2 or 50 returns the cash drawer status. <br>
 */
+(NSData *) returnState:(int) n;
/**
 Print raster bitmap<br>
 GS V 0 m<br>
 (PrintRasterType) m: print mode. <br>
 (UIImage *) image: Picture object. <br>
 (BmpType) type: The method of image processing, binary method or dithering algorithm processing. <br>
 
 */
+(NSData *) printRasteBmpWithM:(PrintRasterType) m andImage:(UIImage *) image andType:(BmpType) type andPaperHeight:(int) paperheight;
/**
 Set barcode width<br>
 GS w n<br>
 1D 77 n<br>
 (int) n:2~6,defualt 3.<br>
 */
+(NSData *) setBarcoeWidth:(int) n;
/**
 Set Chinese character mode<br>
 FA! N<br>
 1C 21 n<br>
 (int) n: 0~255, the different bits of n define the character mode.
 */
+(NSData *) setChineseCharacterModel:(int) n;
/**
 Select Chinese character mode<br>
 FS &<br>
 1C 26<br>
 */

+(NSData *) selectChineseCharacterModel;
/**
 Select or cancel the Chinese character underline mode<br>
 FS-n<br>
 1C 2D n<br>
 (int) n:0~2 or 48~50.<br>
 */

+(NSData *) selectOrCancelChineseCharUnderLineModel:(int) n;
/**
 Cancel Chinese Character Mode<br>
 FS .<br>
 1C 2E<br>
 */

+(NSData *) CancelChineseCharModel;
/**
 Define user-defined Chinese characters<br>
 FS 2 c1 c2 d1...dk<br>
 1C 32 FE c2 d1...dk<br>
 (int) c2: A1H<=c2<=FEH.<br>
 (Byte*) bytes: represents the byte array of Chinese character data. <br>
 */
+(NSData *) definedUserDefinedChineseCharWithCMition:(int) c2 andNsdata:(Byte *) bytes;
/**
 Set the left and right spacing of Chinese characters<br>
 FS S n1 n2<br>
 1C 53 n1 n2<br>
 (int) n1: left spacing, 0~255.<br>
 (int) n2: Right spacing, 0~255.<br>
 */
+(NSData *) setChineseCharLeftAndRightSpaceWithN1:(int) n1 andN2:(int) n2;
/**
 Select or cancel double width and double width of Chinese characters<br>
 FS W n<br>
 1C 57 n<br>
 (int) n:0~255, the lowest bit of n is 1, which means selection, and 0 means cancellation. <br>
 */

+(NSData *) selectOrCancelChineseCharDoubleWH:(int) n;
/**
 Buzzer prompt when the printer comes to print the order<br>
 ESC B n t<br>
 1B 42 n t<br>
 (int) n: Number of beeps, 1~9.<br>
 (int) t: t*50ms represents the time of each beep, 1~9.<br>
 */
+(NSData *) printerOrderBuzzingHintWithRes:(int) n andTime:(int) t;
/**
 The printer comes with a single buzzer and the warning light flashes<br>
 ESC C m t n<br>
 1B 43 m t n<br>
 (int) m: the number of buzzers, the number of flashes of the alarm light, 1~20.<br>
 (int) t: (t*50ms) represents the interval time, 1~20.<br>
 (int) n: 0~3, respectively representing whether to tweet or not, flashing.<br>
 */
+(NSData *) printerOrderBuzzingAndWaringLightWithM:(int) m andT:(int) t andN:(int) n;
/**
 QRCODE: set cell size<br>
 GS (0 g n<br>
 1D 28 6B 30 67 n<br>
 (int) n:0~255.<br>
 */

+(NSData *) setQRcodeUnitsize:(int) n;
/**
 Set error correction level<br>
 GS (0 i n<br>
 1D 28 6B 30 69 n<br>
 */

+(NSData *) setErrorCorrectionLevelForQrcode:(int) n;
/**
 Transfer data to the encoding buffer<br>
 GS (0 & nL nH d1...dk<br>
 1D 28 6B 30 80 nL nH d1...dk<br>
 (NSString *) str: The content of the QR code. <br>
 */

+(NSData *) sendDataToStoreAreaWitQrcodeConent:(NSString *) str usEnCoding:(NSStringEncoding) strEnCoding;
/**
 Print the QR code of the encoding buffer
 GS (0 ?<br>
 1D 28 6B 30 81<br>
 */

+(NSData *) printTheQRcodeInStore;

/**
 Set the number of columns in the data region<br>
 1D 28 6B 03 00 30 41 n<br>
 
 */

+(NSData *) setPdf417Columns:(int) n;

/**
 set the width of the moudule<br>
 1D 28 6B 03 00 30 43 n<br>
 
 */

+(NSData *) setpdf417WidthOfModule:(int) n;

/**
 set the row height<br>
 1D 28 6B 03 00 30 44 n<br>
 
 */

+(NSData *) setpdf417RowHeight:(int) n;

/**
 store the data in the symbol storage area<br>
 1D 28 68 F9 00 30 50 30 d1...dk<br>
 
 */
+(NSData *) storethepdf417WithpL:(int) pL andpH:(int) pH andContent:(NSString*) content usEnCoding:(NSStringEncoding) strEnCoding;

/**
 print the pdf417 symbol data in the symbol storage area<br>
 1D 28 6B 03 00 30 51 n<br>
  */
+(NSData *)printPdf417InStore;

//Newly added command
+(NSData *)openOrCloseLableModelInRecep:(BOOL) model;

+(NSData *)endOfLabel;

+(NSData *)checkLableAndGap;

+(NSData *)setLableWidth:(int) width;

+(NSData *)printQRCode:(int )n level:(int)errLevel code:(NSString *)code useEnCodeing:(NSStringEncoding)strEncoding;

+(NSData *)setTempData;
+(NSData *)setTempData2;

+(NSData *) printcodaBarcodeWithM:(int) m andContent:(NSString *) content useEnCodeing:(NSStringEncoding) strEncoding;

+(NSData *) printcodaUPCEWithM:(int) m andContent:(NSString *) content useEnCodeing:(NSStringEncoding) strEncoding;

+(NSData *)print93BarcodeWithM:(int)m andN:(int)n andContent:(NSString *)content useEnCodeing:(NSStringEncoding) strEnCoding;

@end

//
//  BLEManage.h
//  
//
//  Created by femto01 on 15/11/20.
//  Copyright © 2015年 WTT. All rights reserved.
//

/**
 *  #define kBLEM [BLEManager sharedBLEManager]
    if (kBLEM.isConnected) {
        [kBLEM writeDataToDevice:@[@(0)] command:1];
        [kBLEM writeDataToDevice:@[@(1),@(2)] command:2];
    }
 *
 *
 */

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
@class BLEManager;

//Scan found device callback block
typedef void (^BleManagerDiscoverPeripheralCallBack) (NSArray *peripherals);
typedef void (^BleManagerConnectPeripheralCallBack) (BOOL isConnected);
typedef void (^BleManagerReceiveCallBack) (CBCharacteristic *characteristic );


/**
 Define agent BLEManagerDelegate
 */
@protocol BLEManagerDelegate <NSObject>
// Discovery of peripherals
- (void)BLEManagerDelegate:(BLEManager *)BLEmanager updatePeripheralList:(NSArray *)peripherals RSSIList:(NSArray *)RSSIArr;
// connection succeeded
- (void)BLEManagerDelegate:(BLEManager *)BLEmanager connectPeripheral:(CBPeripheral *)peripheral;
// Disconnect
- (void)BLEManagerDelegate:(BLEManager *)BLEmanager disconnectPeripheral:(CBPeripheral *)peripheral isAutoDisconnect:(BOOL)isAutoDisconnect;
// Failed to connect to device
- (void)BLEManagerDelegate:(BLEManager *)BLEmanager didFailToConnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error;
// Data received
//- (void)BLEManagerDelegate:(BLEManager *)BLEmanager didReceiveDataFromPrinter:(CBCharacteristic *)characteristic;
// Send data successfully
- (void)BLEManagerDelegate:(BLEManager *)BLEmanager didWriteValueForCharacteristic:(CBCharacteristic *)character error:(NSError *)error;
@end


@interface BLEManager : NSObject <CBCentralManagerDelegate, CBPeripheralDelegate> {
    CBCharacteristic *write_characteristic;
    CBCharacteristic *read_characteristic;
    int commandSendMode; //Command sending mode. 0: send immediately 1: batch send
}

#pragma mark -

@property (nonatomic,assign) id<BLEManagerDelegate> delegate;

#pragma mark 基本属性

@property (strong, nonatomic) CBCentralManager *manager;        //BLE Management Center

@property (strong, nonatomic) CBPeripheral     *peripheral;     //Peripherals-Bluetooth hardware

@property (nonatomic,assign ) BOOL             isConnected;   //Connection success:YES, failure:NO

@property (nonatomic,assign ) BOOL             isAutoDisconnect;     //Whether to connect automatically, on:YES, off:NO

@property (atomic,assign    ) BOOL           connectStatu;  // Bluetooth connection status

@property (strong, nonatomic  ) NSMutableArray        *peripherals; // All hardware devices discovered

@property (strong, nonatomic) NSMutableArray *connectedPeripherals; //Peripherals connected

@property (strong, nonatomic) NSMutableArray *RSSIArray;// Bluetooth signal array

@property (assign, readonly) BOOL isScaning; //scanning on:YES, off:NO

// Send data to the specified peripheral
@property (nonatomic,strong) CBPeripheral *writePeripheral;
/**
 * Completion block for peripheral scanning
 */
@property (copy, nonatomic) BleManagerDiscoverPeripheralCallBack scanBlock;

@property (nonatomic,strong) NSMutableArray *dataArray;
@property (nonatomic,strong) NSMutableArray *commandBuffer;
/*
 *Completion block for peripheral scanning
 */
@property (copy, nonatomic) BleManagerConnectPeripheralCallBack connectBlock;
/*
 *Receive data callback
 */
@property (nonatomic,copy) BleManagerReceiveCallBack receiveBlock;
#pragma mark -
#pragma mark Basic methods
/**
 *  Singleton method
 *
 *  @return self
 */
+ (instancetype)sharedBLEManager;

/*
 *  Get mobile phone Bluetooth status
 */
- (BOOL)isLECapableHardware;

/**
 *  Turn on Bluetooth scanning
 */
- (void)startScan;

/*
 *  Start scanning and stop after 'scanInterval' seconds
 */
- (void)startScanWithInterval:(NSInteger)scanInterval completion:(BleManagerDiscoverPeripheralCallBack)callBack;

/**
 *  Stop scanning
 */
- (void)stopScan;

/**
 *  Connect to specified device
 */
- (void)connectPeripheral:(CBPeripheral *)peripheral;

/*
 *  Connect Bluetooth device
 */
- (void)connectPeripheral:(CBPeripheral *)peripheral completion:(BleManagerConnectPeripheralCallBack)callBack;

/*
 *  Try to reconnect
 */
- (void)reConnectPeripheral:(CBPeripheral *)peripheral;

/**
 *  Disconnect
 */
- (void)disconnectPeripheral:(CBPeripheral *)peripheral;


#pragma mark -
#pragma mark Customize other attributes
/**
 *  Write data to the device
 *
 * @param dataArray The data to be written
 * @param command command value,
 *  1=message reminder,
 *  2=running goal,
 *  3=light reminder when running to complete the goal,
 *  4=set low battery light reminder,
 *  5=set light normally on color,
 *  6=light normally on time,
 *  7=Light normally on mode,
 *  8=Set device time
 */
//- (void)writeDataToDevice:(NSArray *)dataArray command:(int)command;

/**
 Send data to the device, the data sent is of type NSString, and the encoding type must be specified
 */
-(void)sendDataWithPeripheral:(CBPeripheral *)peripheral withString:(NSString *)dataString coding:(NSStringEncoding)EncodingType;

/**
 Send instructions to the printer
 */
-(void)writeCommadnToPrinterWthitData:(NSData *)data;

/**
 Send instructions to the printer with callback method
 */
-(void)writeCommadnToPrinterWthitData:(NSData  *)data withResponse:(BleManagerReceiveCallBack)block;



-(void)reScan;  /**Disconnect rescan of existing devices*/

-(void)disconnectRootPeripheral;  //Disconnect current device

//#pragma mark-=================== M instruction===================
//#pragma mark-other methods
///**
// * 1. Horizontal positioning
// */
//- (void)horizontalMition;
///**
// * 2. Print and wrap
// */
//- (void)printAndFeed;
///**
// * 3. Print and return to standard mode
// */
//- (void)printAndBackToNormalModel;
///**
// * 4. Cancel printing data in page mode
// */
//- (void)cancelPrintData;
///**
// * 5. Real-time status transmission
// */
//- (void)updataPrinterState:(int)n
// completion:(BleManagerReceiveCallBack)callBlock;
///**
// * 6. Real-time request to the printer
// */
//- (void)updataPrinterAnswer:(int) n;
///**
// * 7. Generate cash drawer opening pulse in real time
// */
//- (void)openBoxAndPulse:(int) n m:(int) m t:(int) t;
///**
// * 8. Print in page mode
// */
//- (void)printOnPageModel;
///**
// * 9. Set the right spacing of characters
// */
//- (void)setCharRightMargin:(int)n;
///**
// * 10. Select print mode
// */
//- (void)selectPrintModel:(int)n;
///**
// * 11.Set the absolute printing position
// */
//- (void)setPrintLocationWithParam:(int)nL nH:(int)nH;
///**
// * 12. Select/cancel user-defined characters
// */
//- (void)selectOrCancelCustomCharacter:(int)n;
//
///**
// * 13.Define user-defined characters
// */
//- (void)definCustomCharacter:(int)y c1:(int)c1 c2:(int)c2 dx:(NSArray *)points;
///**
// * 14.Select bitmap mode
// */
//- (void)selectBitmapModel:(int)m nL:(int)nL nH:(int)nH dx:(NSArray *)points;
//
///**
// * 15. Cancel the underline mode
// */
//- (void)cancelUnderLineModel:(int)n;
///**
// * 16.Set the default line spacing
// */
//- (void)setDefaultLineMargin;
///**
// * 17. Set line spacing
// */
//- (void)setLineMargin:(int)n;
///**
// * 18.Select printer
// */
//- (void)selectPrinter:(int)n;
///**
// * 19. Cancel user-defined characters
// */
//- (void)cancelCustomCharacter:(int)n;
///**
// * 20. Initialize the printer
// */
//- (void)initializePrinter;
///**
// * 21. Set the horizontal tab position
// */
//- (void)setTabLocationWith:(NSArray *)points;
///**
// * 22. Select/cancel bold mode
// */
//- (void)selectOrCancelBoldModel:(int)n;
///**
// * 23. Select/cancel double printing mode
// */
//- (void)selectOrCancelDoublePrintModel:(int)n;
///**
// * 24. Print and feed paper
// */
//- (void)printAndPushPage:(int)n;
///**
// * 25. Select page mode
// */
//- (void)selectPageModel;
///**
// * 26. Choose font
// */
//- (void)selectFont:(int)n;
///**
// * 27. Choose an international character set
// */
//- (void)selectINTL_CHAR_SETWith:(int)n;
///**
// * 28. Select standard mode
// */
//- (void)selectNormalModel;
///**
// * 29. Select the print area direction in page mode
// */
//- (void)selectPrintDirectionOnPageModel:(int)n;
///**
// * 30. Select/Cancel rotate 90 degrees clockwise
// */
//- (void)selectOrCancelRotationClockwise:(int)n;
///**
// * 31. Set print area in page mode
// */
//- (void)setprintLocationOnPageModelWithXL:(int)xL
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
// */
//- (void)setHorizonLocationWith:(int)nL nH:(int)nH;
///**
// * 33. Choose alignment
// */
//- (void)selectAlignmentWithN:(int)n;
///**
// * 34. Select paper sensor to output signal
// */
//- (void)selectSensorForOutputSignal:(int)n;
///**
// * 35. Select the paper sensor to stop printing
// */
//- (void)selectSensorForStopPrint:(int)n;
///**
// * 36. Allow/Prohibit keys
// */
//- (void)allowOrDisableKeypress:(int)n;
///**
// * 37. Print and feed the paper forward N lines
// */
//- (void)printAndPushPageRow:(int)n;
///**
// * 38. Generate cash drawer control pulse
// */
//- (void)makePulseWithCashboxWithM:(int)m t1:(int)t1 t2:(int)t2;
///**
// * 39. Select the character code table
// */
//- (void)selectCharacterTabN:(int)n;
///**
// * 40. Select/cancel upside down printing mode
// */
//- (void)selectOrCancelInversionPrintModel:(int)n;
///**
// * 41. Print the bitmap downloaded to FLASH
// */
//- (void)printFlashBitmapWithN:(int)n m:(int)m;
///**
// * 42. Define FLASH bitmap
// */
//- (void)definFlashBitmapWithN:(int)n Points:(NSArray *)points;
///**
// * 43. Choose character size
// */
//- (void)selectCharacterSize:(int)n;
///**
// * 44. Set the vertical absolute position in page mode
// */
//- (void)setVertLocationOnPageModelWithnL:(int)nL nH:(int)nH;
///**
// * 45. Define download bitmap
// */
//- (void)defineLoadBitmapWithX:(int)x Y:(int)y Points:(NSArray *)points;
///**
// * 46. Perform hexadecimal dump of print data
// */
//- (void)printDataAndSaveAsHexWithpL:(int)pL pH:(int)pH n:(int)n m:(int)m;
///**
// * 47. Print and download bitmap
// */
//- (void)printLoadBitmapM:(int)m;
///**
// * 48. Start/end macro definition
// */
//- (void)beginOrEndDefine;
///**
// * 49. Select/cancel black and white reverse printing mode
// */
//- (void)selectORCancelBWPrintModel:(int)n;
///**
// * 50. Select the printing position of HRI characters
// */
//- (void)selectHRIPrintLocation:(int)n;
///**
// * 51. Set the left margin
// */
//- (void)setLeftMarginWithnL:(int)nL nH:(int)nH;
///**
// * 52. Set horizontal and vertical movement units
// */
//- (void)setHoriAndVertUnitXWith:(int)x y:(int)y;
///**
// * 53. Select the cutting mode and cut the paper
// */
//- (void)selectCutPaperModelAndCutPaperWith:(int)m n:(int)n selectedModel:(int)model;
///**
// * 54. Set the width and height of the print area
// */
//- (void)setPrintLocationWith:(int)nL nH:(int)nH;
///**
// * 55. Set the vertical relative position in page mode
// */
//- (void)setVertRelativeLocationOnPageModelWith:(int)nL nH:(int)nH;
///**
// * 56. Execute macro commands
// */
//- (void)runMacroMommandWith:(int)r t:(int)t m:(int)m;
///**
// * 57. Turn on/off the automatic status return function (ASB)
// */
//- (void)openOrCloseASB:(int)n;
///**
// * 58. Choose HRI to use font
// */
//- (void)selectHRIFontToUse:(int)n;
///**
// * 59. Choose barcode height
// */
//- (void)selectBarcodeHeight:(int)n;
///**
// * 60. Print barcode
// */
//- (void)printBarCodeWithPoints:(int)m n:(int)n points:(NSArray *)points selectModel:(int)model;
///**
// * 61. Return status
// */
//- (void)callBackStatus:(int)n completion:(BleManagerReceiveCallBack)block;
///**
// * 62. Print raster bitmap
// */
//- (void)printRasterBitmapWith:(int)m
// xL:(int)xL
// xH:(int)xH
// yl:(int)yL
// yh:(int)yH
// points:(NSArray *)points;
///**
// * 63. Set the barcode width
// */
//- (void)setBarcodeWidth:(int)n;
//#pragma mark-============Chinese character control command============
///**
// * 64. Set Chinese character mode
// */
//- (void)setChineseCharacterModel:(int)n;
///**
// * 65. Select Chinese character mode
// */
//- (void)selectChineseCharacterModel;
///**
// * 66. Select/cancel Chinese character underline mode
// */
//- (void)selectOrCancelChineseUderlineModel:(int)n;
///**
// * 67. Cancel Chinese character mode
// */
//- (void)cancelChineseModel;
///**
// * 68. Define user-defined Chinese characters
// */
//- (void)defineCustomChinesePointsC1:(int)c1 c2:(int)c2 points:(NSArray *)points;
///**
// * 69. Set the left and right spacing of Chinese characters
// */
//- (void)setChineseMarginWithLeftN1:(int)n1 n2:(int)n2;
///**
// * 70. Select/cancel double height and width of Chinese characters
// */
//- (void)selectOrCancelChineseHModelAndWModel:(int)n;
//#pragma mark-============Printer prompt command============
///**
// * 72. Buzzer prompt when the printer comes to print the order
// */
//- (void)printerSound:(int)n t:(int)t;
///**
// * 73. The buzzer and warning light flashes when the printer comes to print the order
// */
//- (void)printerSoundAndAlarmLight:(int)m t:(int)t n:(int)n;
//
//#pragma mark-=========TSC instruction==========
///**
// * 1. Set label size
// */
//- (void)MaddSizeWidth:(int)width height:(int)height;
///**
// * 2. Set the gap length
// */
//- (void)MaddGap:(int)gap;
///**
// * 3. Generate cash drawer control pulse
// */
//- (void)MaddCashDrwer:(int)m t1:(int)t1 t2:(int)t2;
///**
// * 4. Control the stop position of each label
// */
//- (void)MaddOffset:(float)offset;
///**
// * 5. Set printing speed
// */
//- (void)MaddSpeed:(float)speed;
///**
// * 6. Set the print density
// */
//- (void)MaddDensity:(int)n;
///**
// * 7. Set printing direction and mirror image
// */
//- (void)MaddDirection:(int)n;
///**
// * 8. Set the origin coordinate
// */
//- (void)MaddReference:(int)x y:(int)y;
///**
// * 9. Clear print buffer data
// */
//- (void)MaddCls;
///**
// * 10. Paper feed
// */
//- (void)MaddFeed:(int)feed;
///**
// * 11. Unload the paper
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
// */
//- (void)MaddPrint:(int)m;
///**
// * 15. Set the international code page
// */
//- (void)MaddCodePage:(int)page;
///**
// * 16.Set the buzzer
// */
//- (void)MaddSound:(int)level interval:(int)interval;
///**
// * 17. Set the printer to report an error
// */
//- (void)MaddLimitFeed:(int)feed;
///**
// * 18.Draw black blocks in the print buffer
// */
//- (void)MaddBar:(int)x y:(int)y width:(int)width height:(int)height;
///**
// * 19. Draw a one-dimensional barcode in the print buffer
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
// */
//- (void)MaddBox:(int)x y:(int)y xend:(int)xend yend:(int)yend;
///**
// * 21. Draw a bitmap in the print buffer
// */
//- (void)MaddBitmap:(int)x
// y:(int)y
// width:(int)width
// height:(int)height
// mode:(int)mode data:(int)data;
///**
// * 22. Erase the data in the specified area in the print buffer
// */
//- (void)MaddErase:(int)x y:(int)y xwidth:(int)xwidth yheight:(int)yheight;
///**
// * 23. Invert the black and white data of the specified area
// */
//- (void)MaddReverse:(int)x y:(int)y xwidth:(int)xwidth yheight:(int)yheight;
///**
// * 24. Draw text in the print buffer
// */
//- (void)MaddText:(int)x y:(int)y font:(NSString *)font rotation:(int)rotation x_mul:(int)xmul y_mul:(int)ymul content:(NSString *)content;
///**
// * 25. Draw text in the print buffer
// */
//- (void)MaddQRCode:(int)x y:(int)y level:(int)level cellWidth:(int)cellWidth rotation:(int)totation data:(NSString *)dataStr;
///**
// * 26. Set whether the stripping function is turned on
// */
//- (void)MaddPeel:(NSString *)enable;
///**
// * 27. Set whether the tear-off function is enabled
// */
//- (void)MaddTear:(NSString *)enable;
///**
// * 28. Set whether the cutter function is turned on
// */
//- (void)MaddCut:(NSString *)enable;
///**
// * 29. When setting the printer error, whether to print the previous content
// */
//- (void)MaddReprint:(NSString *)enable;
///**
// * 30. Set whether to press the paper feed button to print the latest label
// */
//- (void)MaddPrintKeyEnable:(NSString *)enable;
///**
// * 31. Set the number of copies of the latest label printed by pressing the paper feed key
// */
//- (void)MaddPrintKeyNum:(int)m;
/**
  * 32. Return the contents of the buffer to be sent
  */
-(NSArray*)GetBuffer;
/**
  * 33. Clear the buffer content
  */
-(void)ClearBuffer;
/**
  * 34. Send buffer command
  */
-(void)SendCommandBuffer;
/**
  * 34. Send a single command
  */
-(void)sendCommand:(NSData *)data;

-(void)MSetCommandMode:(int)Mode;
@end


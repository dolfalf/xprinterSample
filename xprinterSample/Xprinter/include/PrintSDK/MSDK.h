//
//  MSDK.h
//  Printer
//
//  Created by apple on 16/4/6.
//  Copyright © 2016年 Admin. All rights reserved.
//


/*
 Introduction: The use of SDK requires adding system dependency libraries
 SystemConfiguration.framework
 CFNetwork.framework
 CoreBluetooth.framework
 
 
 XprinterIosSdkのusrファイルに表示されるヘッダーファイル（.hファイル）は、
 MBLEManager.h、MWIFIManager.h、TscCommand.h、MCommand.h、ImageTranster.h、およびMSDK.hです。
 これらの.hファイルには、Bluetoothとwifiの接続（MBLEMananger.hとMWIFIManager）、
 データの送受信方法と従う必要のあるエージェント、および命令カプセル化のツールクラス（TscCommand、MCommand、ImageTranster）が含まれます。
 
 MSDK.h　ドキュメント
  
 MBLEManager.h
 Bluetooth接続とMコマンドの送信を処理するBluetooth管理クラスです。
 [MBLEManager sharedInstance]シングルトンメソッドを使用して管理オブジェクトを作成し、作成中にプロキシを追跡し、プロキシメソッドを実装します。
 MstartScanメソッドを呼び出してスキャンを開始し、プロキシメソッドMdidUpdatePeripheralListでスキャン結果を取得します。
 MconnectDevice：指定された周辺機器に接続するためのBluetooth接続方法です。
 MBLEManagerにはwritePeripheral属性があります。これは、データを書き込むペリフェラルを指定するために使用され、デフォルトのビットに最後に接続されているペリフェラルを指定しません。
 
 MWIFIManager.h
 wifi接続とバーコードコマンドの送信を処理するwifi管理クラスです。
 シングル接続では、シングルトンメソッド[MWIFIManager shareWifiManager]を使用して接続オブジェクトを作成し、プロキシに従います。
 MConnectWithHost：port：completion：は接続メソッドであり、IPとポート番号を指定し、ブロックコールバックが成功するかどうかを指定します。
 複数の接続の場合は、[[MWIFIManager alloc] init]メソッドを使用して複数の管理オブジェクトを初期化し、保存し、対応するオブジェクトを使用して命令を送信します。
 
 TscCommand.h
 バーコードコマンドパッケージツールクラス、すべての戻り値はNSDataタイプです。
 MCommand.h
 Mコマンドカプセル化ツールクラス、戻り値はNSDataタイプです。
 これら2つの命令ツールクラスのメソッドは、クラス名によって直接呼び出されるクラスメソッドであり、戻り値はNSData型であり、データを直接送信するために使用できます。
 BluetoothおよびWiFi接続の実現には、プロキシに従う必要があります。詳細については、サンプルコードを参照してください。
 MBLEManager.hおよびMWIFIManager.hでデータを送信する特定のメソッドは、
 -（void）MWriteCommandWithData：（NSData *）data;およびコールバックを使用するメソッドです。
 -（void）MWriteCommandWithData：（NSData *）data callBack：（MTSCCompletionBlock）block;
 
 Bluetooth管理クラスの使用手順：
  まず、[MBLEManager sharedInstance]シングルトンメソッドを使用して、管理オブジェクトを作成し、プロキシを設定して、プロキシメソッドを実装します。
  注：MBLEManagerオブジェクトが作成されると、Bluetoothがオンになってスキャンされ、スキャン結果も保存されます。この時点で、実装されたプロキシメソッド
  -（void）MdidUpdatePeripheralList：（NSArray *）peripherals RSSIList：（NSArray *）rssiList;で、
  スキャン結果を取得でき、スキャンされたデバイスMconnectDevice：;を介して接続できます。成功または失敗すると、プロキシメソッドが呼び出されます
  -（void）MdidConnectPeripheral：（CBPeripheral *）peripheral;および
  -（void）MdidFailToConnectPeripheral：（CBPeripheral *）peripheral error：（NSError *）error;メソッド。
  接続が成功したら、データの書き込みの特性を取得し、データを送信するメソッドを呼び出すことができます。
  送信するには、MWriteCommandWithData：メソッドを使用することをお勧めします。
  データが送信された後、プロキシメソッド
  MdidWriteValueForCharacteristic：（CBCharacteristic *）character error：（NSError *）errorがコールバックされます。
  errorを使用して、データが正常に送信されたかどうかを判断し、対応する操作を実行できます。
  MWriteCommandWithData：callblock：メソッドを使用して送信し、ブロックを使用して成功したかどうかをコールバックすることもできます。
 
 
 @protocol MBLEManagerDelegate <NSObject>
// Execute after the discovered Bluetooth device
-(void)MdidUpdatePeripheralList:(NSArray *)peripherals RSSIList:(NSArray *)rssiList;
// Execute after successful connection
-(void)MdidConnectPeripheral:(CBPeripheral *)peripheral;
// Execute after connection failure
-(void)MdidFailToConnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error;
// Execute after disconnection
-(void)MdidDisconnectPeripheral:(CBPeripheral *)peripheral isAutoDisconnect:(BOOL)isAutoDisconnect;
// Execute after sending data
-(void)MdidWriteValueForCharacteristic:(CBCharacteristic *)character error:(NSError *)error;
@end
 
 Wi-Fi管理の手順：
 シングル接続はシングルトンメソッド[MWIFIManager shareWifiManager]を使用して、接続オブジェクトを作成し、プロキシを設定し、プロキシメソッドを実装できます。
 MConnectWithHost：port：completion：は接続方法です。IPとポート番号、およびブロックコールバックが成功するかどうかを指定します。 プロキシメソッド
 -（void）MWIFIManager：（MWIFIManager *）manager didConnectedToHost：（NSString *）host port：（UInt16）port;
 を実装して、接続が成功または失敗した後の操作を処理することもできます。
 
 @protocol MWIFIManagerDelegate <NSObject>
 // Execute after successfully connecting to the host
 -(void)MWIFIManager:(MWIFIManager *)manager didConnectedToHost:(NSString *)host port:(UInt16)port;
 // Disconnect
 -(void)MWIFIManager:(MWIFIManager *)manager willDisconnectWithError:(NSError *)error;
 // Execute after writing data
 -(void)MWIFIManager:(MWIFIManager *)manager didWriteDataWithTag:(long)tag;
 // Method to be executed after receiving data method
 -(void)MWIFIManager:(MWIFIManager *)manager didReadData:(NSData *)data tag:(long)tag;
 // method executed after disconnection
 -(void)MWIFIManagerDidDisconnected:(MWIFIManager *)manager;
 @end
 */


#ifndef MSDK_h
#define MSDK_h

#import "MBLEManager.h"
#import "MWIFIManager.h"
#endif /* MSDK_h */

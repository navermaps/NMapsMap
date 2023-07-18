
#import <NMapsMap/NMapsMap.h>

NS_ASSUME_NONNULL_BEGIN
  
#pragma mark - NMFLoggingCongifuration

typedef NS_ENUM(NSInteger, NMFLoggingLevel) {
    NMFLoggingLevelNone = 0,
    NMFLoggingLevelFault,
    NMFLoggingLevelError,
    NMFLoggingLevelWarning,
    NMFLoggingLevelInfo,
    NMFLoggingLevelDebug,
    NMFLoggingLevelVerbose,
};

typedef void (^NMFLoggingBlockHandler)(NMFLoggingLevel level, NSString * _Nonnull filePath, NSUInteger line, NSString * _Nonnull message);

@interface NMFLoggingConfiguration : NSObject
@property (nonatomic, copy, null_resettable) NMFLoggingBlockHandler handler;
@property (assign, nonatomic) NMFLoggingLevel loggingLevel;
@property (class, nonatomic, readonly, nonnull) NMFLoggingConfiguration *sharedConfiguration;
- (NMFLoggingBlockHandler _Nullable)handler UNAVAILABLE_ATTRIBUTE;
- (void)logCallingFunction:(const char * _Nonnull)callingFunction functionLine:(NSUInteger)functionLine messageType:(NMFLoggingLevel)type format:(id _Nonnull)messageFormat, ...;
@end

#pragma mark - NMFMarker hidden API

typedef NS_ENUM(NSInteger, OverlayAlign) {
    /**
     가운데.
     */
    OverlayAlignCenter,
    
    /**
     왼쪽.
     */
    OverlayAlignLeft,
    
    /**
     오른쪽.
     */
    OverlayAlignRight,
    
    /**
     위.
     */
    OverlayAlignTop,
    
    /**
     아래.
     */
    OverlayAlignBottom,
    
    /**
     왼쪽 위.
     */
    OverlayAlignTopLeft,
    
    /**
     오른쪽 위.
     */
    OverlayAlignTopRight,
    
    /**
     오른쪽 아래.
     */
    OverlayAlignBottomRight,
    
    /**
     왼쪽 아래.
     */
    OverlayAlignBottomLeft
};

@interface NMFAlignType (Private)
+ (NMFAlignType * _Nonnull)typeWithEnum:(OverlayAlign)alignEnum;
@property(nonatomic, readonly) OverlayAlign enumValue;
@end

@interface NMFMarker (Private)
/**
 마커 캡션의 폰트 패밀리 목록. 폰트는 서버에서 제공되므로 지정한 폰트가 존재하지 않을 수 있다. 목록으로 지정할 경우 글자를 표현할 수
 있는 첫 번째 폰트가 사용된다. 지정한 모든 폰트가 적합하지 않거나 아무 폰트도 지정하지 않을 경우 서버의 기본 폰트를 사용한다.
 */
@property(nonatomic, nullable) NSArray<NSString *> *captionFontFamily;

/**
 마커 서브캡션의 폰트 패밀리 목록. 폰트는 서버에서 제공되므로 지정한 폰트가 존재하지 않을 수 있다. 목록으로 지정할 경우 글자를 표현할 수
 있는 첫 번째 폰트가 사용된다. 지정한 모든 폰트가 적합하지 않거나 아무 폰트도 지정하지 않을 경우 서버의 기본 폰트를 사용한다.
 */
@property(nonatomic, nullable) NSArray<NSString *> *subCaptionFontFamily;

/**
 마커가 다른 마커와 충돌해 사라지더라도 공간을 차지할지 여부를 지정합니다.
 공간을 차지할 경우 `YES`, 그렇지 않을 경우 `NO`. 기본값은 `NO`입니다.
 */
@property(nonatomic) BOOL occupySpaceOnCollision;

@end


#pragma mark - NMFSymbol hidden API

@interface NMFSymbol (Private)
/**
 심벌의 유형
 */
@property(nonatomic, readonly, nonnull) NSString *type;
/**
 심벌의 id
 */
@property(nonatomic, readonly, nonnull) NSString *id;
@end


#pragma mark - NMFAuthManager hidden API

@interface NMFAuthManager (Private)
typedef void (^NMFAuthBlockType)(NSData * _Nullable, NMFAuthState, NSError * _Nullable);
typedef NSString*__nonnull(^NMFAuthHMACBlockType) (NSString * __nonnull url);
/**
 인증을 위한 파트너 ID
 */
@property(nonatomic, readwrite, nullable) NSString *partnerId;
/**
 인증용 url HMAC 변환을 위한 block 메소드
 */
@property(nonatomic, nullable) NMFAuthHMACBlockType hmacConverter;

/**
 인증 베타서버 이용 여부
 */
@property(nonatomic, assign) BOOL beta;

/**
 인증 실패시 에러창 보여주기 여부
 */
@property(nonatomic, assign) BOOL showErrorAlert;

/**
 파트너 인증 강제 호출
 */
- (void)partnerAuthorize:(NMFAuthBlockType _Nullable)complete;

/**
 NCP 인증 강제 호출
 */
- (void)ncpAuthorize:(NMFAuthBlockType _Nullable)complete;

@end


#pragma mark - NMFSource & NMFTileSource hidden API

@interface NMFTileset : NSObject
@property (nonatomic, readonly, nullable) NSArray<NSString *> *tiles;
@property (nonatomic, readonly) NSString *version;
@end

@interface NMFSource : NSObject
@property (nonatomic, copy) NSString *identifier;
@property (nonatomic, readonly) BOOL loaded;
@end

@interface NMFTileSource : NMFSource
@property (nonatomic, readonly, nullable) NMFTileset *appliedTileset;
@property (nonatomic, copy, nullable, readonly) NSURL *configurationURL;
@end


#pragma mark - NMFStyle & NMFStyleLayer hidden API

@class NMFStyleLayer;

@interface NMFStyle : NSObject
@property (readonly, copy, nullable) NSString *name;
@property (nonatomic, strong) NSArray<__kindof NMFStyleLayer *> *layers;
- (nullable NMFStyleLayer *)layerWithIdentifier:(NSString *)identifier;
- (nullable NMFSource *)sourceWithIdentifier:(NSString *)identifier;
- (void)addLayer:(NMFStyleLayer *)layer;
- (void)insertLayer:(NMFStyleLayer *)layer atIndex:(NSUInteger)index;
- (void)insertLayer:(NMFStyleLayer *)layer belowLayer:(NMFStyleLayer *)sibling;
- (void)insertLayer:(NMFStyleLayer *)layer aboveLayer:(NMFStyleLayer *)sibling;
- (void)loadSource:(NMFSource *)source;
@end


#pragma mark - NMFMapViewPrivateDelegate hidden API

/**
 맵뷰에 관련된 업데이트 및 비동기 작업들에 대한 결과를 알려주는 콜백 메서드가 정의된 프로토콜.
 */
@protocol NMFMapViewPrivateDelegate <NSObject>

@optional

/**
 맵뷰의 로딩이 시작될때 호출됩니다.
 
 @param mapView 로딩이 시작되는 맵뷰.
 */
- (void)mapViewWillStartLoadingMap:(NMFMapView *)mapView;

/**
 맵뷰의 로딩이 끝나면 호출됩니다.
 
 @param mapView 로딩이 끝난 맵뷰.
 */
- (void)mapViewDidFinishLoadingMap:(NMFMapView *)mapView;

/**
 맵뷰를 보여줄때 필요한 데이터를 로딩하지 못했을때 호출됩니다.
 
 @param mapView 데이터를 불러오지 못한 맵뷰.
 @param error 로딩에 실패한 에러 메세지.
 */
- (void)mapViewDidFailLoadingMap:(NMFMapView *)mapView withError:(NSError *)error;

/**
 OpenGL ES 렌더링이 시작될때 호출됩니다.
 
 @param mapView 렌더링이 시작될 맵뷰.
 */
- (void)mapViewWillStartRenderingMap:(NMFMapView *)mapView;

/**
 OpenGL ES 렌더링이 완료될때 호출됩니다.
 
 @param mapView 렌더링이 완료된 맵뷰.
 */
- (void)mapViewDidFinishRenderingMap:(NMFMapView *)mapView fullyRendered:(BOOL)fullyRendered;

/**
 맵뷰가 redraw 되는 시점에 호출됩니다.
 `-mapView:CameraIsChangingByReason:` 보다도 빈번하게 호출되기 때문에 성능에 영향을 줄 여지가 있습니다.
 
 @param mapView redraw되는 맵뷰.
 */
- (void)mapViewWillStartRenderingFrame:(NMFMapView *)mapView;

/**
 맵뷰의 redraw가 끝났을때 호출됩니다.
 `-mapView:CameraIsChangingByReason:` 보다도 빈번하게 호출되기 때문에 성능에 영향을 줄 여지가 있습니다.
 
 @param mapView redrawn가 끝난 맵뷰.
 */
- (void)mapViewDidFinishRenderingFrame:(NMFMapView *)mapView fullyRendered:(BOOL)fullyRendered;

/**
 style 로딩이 끝났을 때 호출됩니다.
 
 새로운 스타일이 불려질때 호출되며
 `-mapViewWillStartRenderingMap:` 와 `-mapViewDidFinishRenderingMap:` 사이에 호출됩니다.
 
 @param mapView style이 로딩되는 맵뷰.
 @param style 로드된 style.
 */
- (void)mapViewDidFinishLoadingStyle:(NMFMapView *)mapView style:(NMFStyle *)style;

/**
 source 로딩이 끝났을 때 호출됩니다.
 
 @param mapView source가 로딩되는 맵뷰.
 @param source 로드된 source.
 */
- (void)mapViewDidFinishLoadingSource:(NMFMapView *)mapView source:(NMFSource *)source;

/**
 실내지도를 켰을 때 호출됩니다.
 실내지도가 지원되는 영역일때 `NMFIndoorRegion`을 전달할 수 있습니다.
 
 @param region 실내지도 영역 데이터.
 */
- (void)updateIndoorRegion:(nullable NMFIndoorRegion *)region;

@end


#pragma mark - NMFIndoorManager hidden API

/**
 실내지도 노출을 담당하는 클래스. 이 클래스의 인스턴스는 직접 생성할 수 없고 `NMFMapView`의 `indoorManager`를
 이용해서 가져올 수 있습니다.
 
 이 클래스는 `NMFMapView`의 `indoorView`에 접근하는 실내지도 관련 속성과 달리
 높은 수준의 기능을 제공합니다. 활성화하면 카메라가 일정 크기 이상 확대되고 실내지도가 있는 영역에 포커스될 경우 자동으로 해당
 영역의 실내지도가 나타납니다.
 */
@interface NMFIndoorManager : NSObject

/**
`NMFIndoorManager`의 위임자.

실내지도 위임자를 이용해 지도에 실내지도 관련 정보를 전달합니다.
*/
@property(nonatomic, weak, nullable) id<NMFIndoorSelectionDelegate> delegate __attribute__((deprecated("Use addDelegate/removeDelegate")));

/**
 실내지도 활성화 여부를 설정합니다. 활성화하면 카메라가 일정 크기 이상 확대되고 실내지도가 있는 영역에 포커스될 경우
 자동으로 해당 영역에 대한 실내지도가 나타납니다.
 
 @return 활성화된 경우 `YES`, 그렇지 않은 경우 `NO`.
 */
@property(nonatomic) BOOL enabled;

@property(nonatomic, weak, nullable) NMFMapView *mapView;
@property(nonatomic, nullable) NMFIndoorRegion *currentRegion;
@property(nonatomic, nullable) NMFIndoorView *requestedView;
@property(nonatomic, nullable) NMFIndoorView *lastView;

/**
 실내지도를 켰을 때 호출되는 메서드.
 실내지도가 지원되는 영역일때 NMFIndoorRegion 을 전달할 수 있습니다.
 
 @param region 실내지도 영역 데이터.
 */
- (void)updateIndoorRegion:(NMFIndoorRegion *_Nullable)region;

@end


#pragma mark - NMFMapView hidden API

@interface NMFMapView (Private)

/**
 유가정보 레이어 휘발유.
 @see `NMFMapView.setLayerGroup(:isEnabled:)`
 */
extern NMF_EXPORT NSString *const NMF_LAYER_GROUP_GAS_PRICE_GASOLINE;

/**
 유가정보 레이어 고급 휘발유.
 @see `NMFMapView.setLayerGroup(:isEnabled:)`
 */
extern NMF_EXPORT NSString *const NMF_LAYER_GROUP_GAS_PRICE_HIGH_OCTANE;

/**
 유가정보 레이어 경유.
 @see `NMFMapView.setLayerGroup(:isEnabled:)`
 */
extern NMF_EXPORT NSString *const NMF_LAYER_GROUP_GAS_PRICE_DIESEL;

/**
 유가정보 레이어 LPG.
 @see `NMFMapView.setLayerGroup(:isEnabled:)`
 */
extern NMF_EXPORT NSString *const NMF_LAYER_GROUP_GAS_PRICE_LPG;

/**
 CCTV 레이어 그룹.
 @see `NMFMapView.setLayerGroup(:isEnabled:)`
 */
extern NMF_EXPORT NSString *const NMF_LAYER_GROUP_CCTV;

/**
 거리뷰 레이어 그룹.
 @see `NMFMapView.setLayerGroup(:isEnabled:)`
 */
extern NMF_EXPORT NSString *const NMF_LAYER_GROUP_PANORAMA;

/**
 항공뷰 레이어 그룹.
 @see `NMFMapView.setLayerGroup(:isEnabled:)`
 */
extern NMF_EXPORT NSString *const NMF_LAYER_GROUP_AIRVIEW;

/**
 맵 뷰의 기본 스타일을 반환합니다.
 
 @return NSURL 객체
 */
- (NSURL *)defaultMapStyle;

- (instancetype)initWithFrame:(CGRect)frame styleURL:(nullable NSURL *)styleURL;

/**
 private delegate
 */
- (void)addPrivateDelegate:(id<NMFMapViewPrivateDelegate> _Nonnull)delegate NS_SWIFT_NAME(addPrivateDelegate(delegate:));
- (void)removePrivateDelegate:(id<NMFMapViewPrivateDelegate> _Nonnull)delegate NS_SWIFT_NAME(removePrivateDelegate(delegate:));

/**
 이 지도의 `NMFStyle` 객체. 항상 같은 객체가 반환됩니다.
 
 @return `NMFStyle` 객체
 */
@property (nonatomic, readonly, nullable) NMFStyle *style;

/**
 map view의 스타일을 정의하는 URL.
 
 URL의 형식은 HTTP나 HTTPS URL이 될 수도 있습니다. 혹은 네이버 지도에서 정의하는 스타일 형식이거나 혹은 리소스에 있는 로컬 파일의 상대 경로로 정의될 수도 있습니다.
 만약 styleURL을 nil로 정의하게 되면 기본 스타일이 적용됩니다.
 */
@property (nonatomic, null_resettable) NSURL *styleURL;

@property (nonatomic, nullable) NSArray<NSString *> *styleUrlStrings;

- (void)applyStyle;

/**
 지도 스타일을 강제로 리로드합니다.
 
 네트워크 변화등의 이유로 스타일이 정상적으로 로딩되지 않았을때 자동적으로 호출되므로,
 일반적인 상황에서 명시적으로 호출할 필요는 없습니다.
 */
- (IBAction)reloadStyle:(id)sender;

/**
 심벌이 숨겨졌는지 여부를 반환합니다.

 @param type  심벌의 타입.
 @param id 심벌의 ID.
 @return 숨겨진 경우 `YES`, 그렇지 않은 경우 `NO`.
 */
- (BOOL)isSymbolHidden:(NSString * _Nonnull)type id:(NSString * _Nonnull)id;

/**
 심벌을 숨기도록 지정하거나 지정 해제합니다.

 @param type  심벌의 타입.
 @param id 심벌의 ID.
 @param hidden 숨길 경우 `YES`, 그렇지 않은 경우 `NO`.
 */
- (void)setSymbolHidden:(NSString * _Nonnull)type id:(NSString * _Nonnull)id hidden:(BOOL)hidden;

/**
 NAVER 로고 버튼 노출 여부.
 기본값 NO
 */
@property (nonatomic, assign) BOOL hiddenLogo;

/**
 3D 객체의 활성화 여부.

 기본값은 `NO`입니다.
 */
@property(nonatomic) BOOL object3dEnabled;

/**
 이 지도에 대한 `NMFIndoorMap` 객체. 항상 같은 객체를 반환합니다.
 */
@property(nonatomic, readonly, nonnull) NMFIndoorManager *indoorManager;

/**
 실내지도를 지정하거나 지정된 실내지도 뷰를 반환합니다. 뷰를 지정하면 해당 실내지도가 지도에 나타납니다. {@link NMFIndoorMap}을 활성화할 경우
 실내지도 뷰가 자동으로 지정되므로 `NMFIndoorMap`과 동시에 사용하는 것은 권장되지 않습니다.
 실내지도를 나타내고 싶지 않을 경우 `nil`을 지정합니다.
 */
@property(nonatomic, nullable) NMFIndoorView *indoorView;

// Debugging the Map
@property (nonatomic) NMFMapDebugMaskOptions debugMask;

// Disabled IsMainThread Exception.
@property (nonatomic, assign) BOOL disabledIsMainThreadException;

- (void)repaint;

@end

@interface NMFMapControlView : UIView
@property(nonatomic, weak) IBOutlet NMFZoomControlView *zoomControlView;
@property(nonatomic, weak) IBOutlet NMFIndoorLevelPickerView *indoorLevelPickerView;
@property(nonatomic, weak) IBOutlet NMFLocationButton *locationButton;
@property(nonatomic, weak) IBOutlet NMFScaleView *scaleView;
@property(nonatomic, weak) IBOutlet NMFCompassView *compassView;
@end

#pragma mark - NMFNaverMapView hidden API

@interface NMFNaverMapFrameView : UIView
@property(nonatomic, weak) IBOutlet NMFMapView *mapView;
@property(nonatomic, weak) IBOutlet NMFMapControlView *controlView;

@property(nonatomic, weak) IBOutlet NSLayoutConstraint *controlViewLeading;
@property(nonatomic, weak) IBOutlet NSLayoutConstraint *controlViewTop;
@property(nonatomic, weak) IBOutlet NSLayoutConstraint *controlViewBottom;
@property(nonatomic, weak) IBOutlet NSLayoutConstraint *controlViewTrailing;

@end


@interface NMFNaverMapView(Private)
@property(nonatomic, weak) NMFNaverMapFrameView *frameView;
@property(nonatomic, assign) BOOL showLogoButton;
@end

#pragma mark - NMFDebug hidden API

@interface NMFDebug : NSObject

+ (BOOL)isDebugActive:(nonnull NMFMapView *)mapView;
+ (void)setDebugOption:(nonnull NMFMapView *)mapView option:(NMFMapDebugMaskOptions)debugOption;
+ (void)cycleDebugOptions:(nonnull NMFMapView *)mapView;

@end


@protocol FpsMeterDelegate;

@interface FpsMeter : NSObject
@property (nonatomic, weak, nullable) id<FpsMeterDelegate> delegate;

+ (nonnull FpsMeter *)fpsMeter:(nonnull NMFMapView *)mapView;

- (void)start;
- (void)stop;
@end


@protocol FpsMeterDelegate <NSObject>
@optional
- (void)onFpsChange:(double)currentFps average:(double)averageFps;

@end


#pragma mark - Clustering

@protocol NMCClusteringKey <NSObject, NSCopying>
@property(nonatomic, nonnull, readonly) NMGLatLng *latLng;
@end

@interface NMCMarkerProperty
@property (nonatomic, readonly) long identifier;
@property (nonatomic, nullable, readonly) NSObject *key;
@property (nonatomic, nullable, readonly) NSObject *tag;
@property (nonatomic, nonnull, readonly) NMGWebMercatorCoord *coord;
@property (nonatomic, nonnull, readonly) NMGLatLng *latLng;
@property (nonatomic, readonly) NSInteger minZoom;
@property (nonatomic, readonly) NSInteger maxZoom;
@property (nonatomic, readonly) NSInteger size;
@end

@interface NMCNode : NSObject
@property (nonatomic, readonly) int64_t identifier;
@property (nonatomic, nullable) NSObject *tag;
@property (nonatomic) NSInteger minZoom;
@property (nonatomic) NSInteger maxZoom;
@property (nonatomic, readonly) NSInteger size;
@property (nonatomic, nonnull, readonly) NMGWebMercatorCoord *coord;
@property (nonatomic, nonnull, readonly) NMGLatLng *latLng;
@end

@interface NMCLeaf : NMCNode
@property (nonatomic, nonnull, readonly) NSObject *key;
@end

@interface NMCCluster : NMCNode
@property (nonatomic, nonnull, readonly) NSArray<NMCNode *> *children;
@end

@protocol NMCMarkerManager
- (NMFMarker * _Nullable)addMarker:(NMCMarkerProperty * _Nonnull)property;
- (void)updateMarker:(NMCMarkerProperty * _Nonnull)property :(NMFMarker * _Nonnull)marker;
- (void)removeMarker:(NMCMarkerProperty * _Nonnull)property :(NMFMarker * _Nonnull)marker;
@end

@interface NMCDefaultMarkerManager : NSObject<NMCMarkerManager>
- (void)updateLeaf:(NMCMarkerProperty * _Nonnull)leaf :(NMFMarker * _Nonnull)marker;
- (void)updateCluster:(NMCMarkerProperty * _Nonnull)cluster :(NMFMarker * _Nonnull)marker;
@end

@protocol NMCThresholdStrategy
- (double)getThreshold:(NSInteger)zoom;
@end

@interface NMCDefaultThresholdStrategy : NSObject<NMCThresholdStrategy>
- (instancetype)initWithThreshold:(double)threshold;
@end

@protocol NMCDistanceStrategy
- (double)getDistance:(NSInteger)zoom Node1:(NMCNode * _Nonnull)node1 Node2:(NMCNode * _Nonnull)node2;
@end

@interface NMCDefaultDistanceStrategy : NSObject<NMCDistanceStrategy>
@end

@protocol NMCPositioningStrategy
- (NMGWebMercatorCoord * _Nonnull)getPosition:(NMCCluster * _Nonnull)cluster;
@end

@interface NMCDefaultPositioningStrategy : NSObject<NMCPositioningStrategy>
@end

@protocol NMCTagMergeStrategy
- (NSObject * _Nullable)mergeTag:(NMCCluster * _Nonnull)cluster;
@end

@interface NMCDefaultTagMergeStrategy : NSObject<NMCTagMergeStrategy>
@end

@interface NMCClusterer<__covariant KeyType : NSObject<NMCClusteringKey> *> : NSObject
@property(nonatomic, weak, nullable) NMFMapView *mapView;
- (BOOL)isEmpty;
- (BOOL)contains:(KeyType _Nonnull)key;
- (void)clear;
- (void)add:(KeyType _Nonnull)key Tag:(NSObject * _Nullable)tag;
- (void)addAll:(NSDictionary<KeyType, NSObject *> * _Nonnull)keyTagMap;
- (void)remove:(KeyType _Nonnull)key;
- (void)removeAll:(NSArray * _Nonnull)keys;
@end

@interface NMCBuilder<__covariant KeyType : NSObject<NMCClusteringKey> *> : NSObject
@property(nonatomic, nonnull) id<NMCThresholdStrategy> thresholdStrategy;
@property(nonatomic, nonnull) id<NMCDistanceStrategy> distanceStrategy;
@property(nonatomic, nonnull) id<NMCPositioningStrategy> positioningStrategy;
@property(nonatomic, nonnull) id<NMCTagMergeStrategy> tagMergeStrategy;
@property(nonatomic, nonnull) id<NMCMarkerManager> markerManager;
@property(nonatomic) NSInteger minClusteringZoom;
@property(nonatomic) NSInteger maxClusteringZoom;
@property(nonatomic) NSInteger minIndexingZoom;
@property(nonatomic) NSInteger maxIndexingZoom;
@property(nonatomic) double maxScreenDistance;
@property(nonatomic) double animationDuration;
@property(nonatomic) BOOL updateOnChange;
- (NMCClusterer<KeyType> * _Nonnull)build;
@end


#pragma mark - Toast

@interface NMFToastManager : NSObject
+ (instancetype)sharedInstance;
- (void)presentWithMessage:(NSString *)message duration:(NSTimeInterval)interval completion:(nullable void (^)(void))completion;
- (void)dismiss;
@end

NS_ASSUME_NONNULL_END

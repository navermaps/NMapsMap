#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "NMFOverlay.h"

@class NMGLineString;

#define NMFDefaultLinePattern @[@2,@1];

/**
 지도에 선을 나타내는 오버레이.
 */
@interface NMFPolylineOverlay : NMFOverlay

/**
 두께. pt 단위.
 
 기본값은 `2.5`입니다.
 */
@property (nonatomic) CGFloat width;

/**
 색상.
 
 기본값은 `UIColor.blackColor`입니다.
 */
@property (nonatomic, copy) UIColor *color;

/**
 끝 지점의 모양.
 
 기본값은 `NMFOverlayLineCapButt`입니다.
 */
@property (nonatomic) NMFOverlayLineCap capType;

/**
 연결점의 모양.
 
 기본값은 `NMFOverlayLineJoinMiter`입니다.
 */
@property (nonatomic) NMFOverlayLineJoin joinType;

/**
 점선 패턴. 패턴은 pt 단위의 배열로 표현되며, 각각 `2n`번째 요소는 실선의 길이,
 `2n + 1`번째 요소는 공백의 길이를 의미하며 빈 리스트를 입력할 경우 실선을 의미합니다.
 */
@property (nonatomic) NSArray<NSNumber *> *pattern;

/**
 좌표열. `points`의 크기는 `2` 이상이어야 합니다.
 */
@property (nonatomic, copy) NSArray<NMGLatLng *> *points;

/**
 좌표열을 지정하여 선 오버레이를 생성합니다. `coords`의 크기는 `2` 이상이어야 합니다.
 
 사용 예시
 ```
 NMGLatLng *p1 = [[NMGLatLng alloc]initWithLat:37.20 lng:127.051]];
 NMGLatLng *p2 = [[NMGLatLng alloc]initWithLat:37.21 lng:127.052]];
 NMGLatLng *p3 = [[NMGLatLng alloc]initWithLat:37.22 lng:127.053]];
 NMFPolylineOverlay *line = [NMFPolylineOverlay polylineOverlayWithPoints:@[p1, p2, p3]];
 [mapView addOverlay:line];
 ```
 
 @param coords 좌표열.
 @return `NMFPolylineOverlay` 객체.
 */
+ (instancetype)polylineOverlayWithPoints:(NSArray<NMGLatLng *> *)coords;

/**
 폴리라인 객체를 지정하여 선 오버레이를 생성합니다.
 
 @param polyline 폴리라인 객체.
 @return `NMFPolylineOverlay` 객체.
 */
+ (instancetype)polylineOverlay:(NMGLineString *)polyline;

/**
 선 오버레이를 생성한 이후 폴리라인을 갱신하기 위한 목적으로 사용할 수 있습니다.

 @param polyline 폴리라인 객체.
 */
- (void)updatePolyline:(NMGLineString *)polyline;

@end

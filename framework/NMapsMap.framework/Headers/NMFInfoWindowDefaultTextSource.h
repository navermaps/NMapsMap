
#import <Foundation/Foundation.h>
#import <UIKit/UIkit.h>

@protocol NMFOverlayImageDataSource;

NS_ASSUME_NONNULL_BEGIN

@interface NMFInfoWindowDefaultTextSource : NSObject <NMFOverlayImageDataSource>

+ (instancetype)dataSource;

@property(nonatomic, readwrite) NSString *title;

@end

NS_ASSUME_NONNULL_END

#import "NMFFoundation.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, NMFRendererType) {
    NMFRendererTypeMetal,
    NMFRendererTypeOpenGL
};

NMF_EXPORT
@interface NMFRendererSelection : NSObject

@end

NS_ASSUME_NONNULL_END

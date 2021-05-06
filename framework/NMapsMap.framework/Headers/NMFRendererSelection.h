#import "NMFFoundation.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, NMFRendererType) {
    NMFRendererTypeOpenGL,
    NMFRendererTypeMetal
};

NMF_EXPORT
@interface NMFRendererSelection : NSObject

@end

NS_ASSUME_NONNULL_END

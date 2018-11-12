#import <Foundation/Foundation.h>

#import "NMFTypes.h"

NS_ASSUME_NONNULL_BEGIN

// Strings in the SDK targets must be retrieved from the framework bundle rather
// than the main bundle, which is usually the application bundle. Redefining
// these macros ensures that the framework bundle’s string tables are used at
// runtime yet tools like genstrings and Xcode can still find the localizable
// string identifiers. (genstrings has an -s option that would allow us to
// define our own macros, but Xcode’s Export Localization feature lacks support
// for it.)
//
// As a consequence of this approach, this header must be included in all SDK
// files that include localizable strings.

#undef NSLocalizedString
#define NSLocalizedString(key, comment) \
    [[NSBundle naverMapFrameworkBundle] localizedStringForKey:(key) value:@"" table:nil]

#undef NSLocalizedStringFromTable
#define NSLocalizedStringFromTable(key, tbl, comment) \
    [[NSBundle naverMapFrameworkBundle] localizedStringForKey:(key) value:@"" table:(tbl)]

#undef NSLocalizedStringWithDefaultValue
#define NSLocalizedStringWithDefaultValue(key, tbl, bundle, val, comment) \
    [[NSBundle naverMapFrameworkBundle] localizedStringForKey:(key) value:(val) table:(tbl)]

@interface NSBundle (NMFAdditions)

/// Returns the bundle containing the SDK’s classes and Info.plist file.
+ (instancetype)naverMapFrameworkBundle;

+ (nullable NSString *)naverMapFrameworkBundleIdentifier;

+ (nullable NSDictionary<NSString *, id> *)naverMapFrameworkInfoDictionary;

+ (nullable NSString *)naverMapApplicationBundleIdentifier;

@property (readonly, copy, nullable) NSString *naverMapFrameworkResourcesDirectory;

@end

NS_ASSUME_NONNULL_END

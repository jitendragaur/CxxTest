// swift-tools-version:5.7
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription
import Foundation

let package = Package(
    name: "StancePackage",
    platforms: [.macOS(.v12)],
    products: [
//        .library(
//            name: "CxxTest",
//            targets: ["CxxTest"]),
//        .library(
//            name: "CxxInterop",
//            targets: ["CxxInterop"]),
    ],
    targets: [
        .target(
            name: "CxxTest",
            dependencies: []
        ),
        .executableTarget(
            name: "CxxInterop",
            dependencies: ["CxxTest"],
            path: "./Sources/CxxInterop",
            sources: [ "main.swift" ],
            swiftSettings: [.unsafeFlags([
                "-I", "Sources/CxxTest/include",
                "-enable-experimental-cxx-interop",
            ])]
        ),
    ]
)


/*
let package = Package(
    name: "cxx-interop-test",
    platforms: [.macOS(.v10_15)],
    products: [
        .executable(
            name: "cxx-interop-test",
            targets: ["cxx-interop-test"]),
    ],
    dependencies: [
    ],
    targets: [
        .target(name: "CXX", dependencies: []),
        .target(
            name: "cxx-interop-test",
            dependencies: ["CXX"],
            path: "./Sources/Swift",
            sources: [ "main.swift" ],
            swiftSettings: [.unsafeFlags([
                // TODO: we shouldn't have to do this. See SRXXXX.
                "-Xfrontend", "-validate-tbd-against-ir=none",
                "-Xfrontend", "-enable-cxx-interop",
                "-I", "Sources/CXX/include",
                "-lc++",
                "-Xfrontend", "-disable-implicit-concurrency-module-import",
                "-Xcc", "-nostdinc++"])]),
    ],
    cxxLanguageStandard: CXXLanguageStandard.cxx14
)
*/

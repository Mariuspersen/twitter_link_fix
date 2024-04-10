const std = @import("std");

pub fn build(b: *std.build.Builder) void {
    const target = b.standardTargetOptions(.{});
    _ = target;
    const optimize = b.standardOptimizeOption(.{ .preferred_optimize_mode = std.builtin.OptimizeMode.ReleaseFast });
    const cflags = [_][]const u8{
        "-Wextra",
        "-Wall",
        "-std=c11",
        "-pedantic"
    };
    const exe = b.addExecutable(.{ .name = "tlf", .optimize = optimize,  });
    exe.linkLibC();
    exe.addCSourceFile(.{
        .file=.{.path="main.c"},
        .flags=&cflags
    });
    b.installArtifact(exe);
}
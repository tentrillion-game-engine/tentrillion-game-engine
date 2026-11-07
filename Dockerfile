FROM alpine:3.24 AS build
WORKDIR /compile
RUN apk update && apk add cmake build-base vulkan-headers \
    vulkan-loader-dev vulkan-tools \
    shaderc glslang-dev libwayland-dev libxkbcommon-dev xorg-dev
RUN addgroup -S nonroot \
    && adduser -S nonroot -G nonroot

FROM scratch
COPY --from=security_provider /etc/passwd /etc/passwd
USER nonroot
COPY --from=build /compile /
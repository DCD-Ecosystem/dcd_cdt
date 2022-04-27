#! /bin/bash

NAME=$1
OS=$2
CDT_PREFIX=${PREFIX}/${SUBPREFIX}
mkdir -p ${PREFIX}/bin/
mkdir -p ${PREFIX}/lib/cmake/${PROJECT}
mkdir -p ${CDT_PREFIX}/bin
mkdir -p ${CDT_PREFIX}/include
mkdir -p ${CDT_PREFIX}/lib/cmake/${PROJECT}
mkdir -p ${CDT_PREFIX}/cmake
mkdir -p ${CDT_PREFIX}/scripts
mkdir -p ${CDT_PREFIX}/licenses

#echo "${PREFIX} ** ${SUBPREFIX} ** ${CDT_PREFIX}"

# install binaries
cp -R ${BUILD_DIR}/bin/* ${CDT_PREFIX}/bin || exit 1
cp -R ${BUILD_DIR}/licenses/* ${CDT_PREFIX}/licenses || exit 1

# install cmake modules
sed "s/_PREFIX_/\/${SPREFIX}/g" ${BUILD_DIR}/modules/DcdCDTMacrosPackage.cmake &> ${CDT_PREFIX}/lib/cmake/${PROJECT}/DcdCDTMacros.cmake || exit 1
sed "s/_PREFIX_/\/${SPREFIX}/g" ${BUILD_DIR}/modules/DcdWasmToolchainPackage.cmake &> ${CDT_PREFIX}/lib/cmake/${PROJECT}/DcdWasmToolchain.cmake || exit 1
sed "s/_PREFIX_/\/${SPREFIX}\/${SSUBPREFIX}/g" ${BUILD_DIR}/modules/${PROJECT}-config.cmake.package &> ${CDT_PREFIX}/lib/cmake/${PROJECT}/${PROJECT}-config.cmake || exit 1

# install scripts
cp -R ${BUILD_DIR}/scripts/* ${CDT_PREFIX}/scripts  || exit 1

# install misc.
cp ${BUILD_DIR}/dcd.imports ${CDT_PREFIX} || exit 1

# install wasm includes
cp -R ${BUILD_DIR}/include/* ${CDT_PREFIX}/include || exit 1

# install wasm libs
cp ${BUILD_DIR}/lib/*.a ${CDT_PREFIX}/lib || exit 1

# install libc++.so
if [[ "$OS" == "ubuntu-16.04" ]]; then
    cp /usr/lib/libc++.so.1.0 ${CDT_PREFIX}/lib || exit 1
    cp /usr/lib/libc++abi.so.1.0 ${CDT_PREFIX}/lib || exit 1
    DIR=`pwd`
    cd ${CDT_PREFIX}/lib || exit 1
    ln -sf libc++.so.1.0 libc++.so.1 || exit 1
    ln -sf libc++abi.so.1.0 libc++abi.so.1 || exit 1
    cd ${DIR} || exit 1
fi

# make symlinks
pushd ${PREFIX}/lib/cmake/${PROJECT} &> /dev/null
ln -sf ../../../${SUBPREFIX}/lib/cmake/${PROJECT}/${PROJECT}-config.cmake ${PROJECT}-config.cmake || exit 1
ln -sf ../../../${SUBPREFIX}/lib/cmake/${PROJECT}/DcdWasmToolchain.cmake DcdWasmToolchain.cmake || exit 1
ln -sf ../../../${SUBPREFIX}/lib/cmake/${PROJECT}/DcdCDTMacros.cmake DcdCDTMacros.cmake || exit 1
popd &> /dev/null

create_symlink() {
   ln -sf ../${SUBPREFIX}/bin/$1 ${PREFIX}/bin/$2 || exit 1
}

create_symlink dcd-cc dcd-cc
create_symlink dcd-cpp dcd-cpp
create_symlink dcd-ld dcd-ld
create_symlink dcd-pp dcd-pp
create_symlink dcd-init dcd-init
create_symlink dcd-wasm2wast dcd-wasm2wast
create_symlink dcd-wast2wasm dcd-wast2wasm
create_symlink dcd-ar dcd-ar
create_symlink dcd-abidiff dcd-abidiff
create_symlink dcd-nm dcd-nm
create_symlink dcd-objcopy dcd-objcopy
create_symlink dcd-objdump dcd-objdump
create_symlink dcd-ranlib dcd-ranlib
create_symlink dcd-readelf dcd-readelf
create_symlink dcd-strip dcd-strip

echo "Generating Tarball $NAME.tar.gz..."
tar -cvzf $NAME.tar.gz ./${PREFIX}/* || exit 1
rm -r ${PREFIX} || exit 1

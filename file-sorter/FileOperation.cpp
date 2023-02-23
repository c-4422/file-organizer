#include "FileOperation.hpp"

FileOperation::FileOperation() :
  mPictures(FileOperation::FileSortSettings({ "jpg", "jpeg", "jfi",
                                            "jpe", "jif", "jfif",
                                            "heif", "heic", "png",
                                            "gif", "svg", "svgz" "eps",
                                            "webp", "tiff", "tif", "ind",
                                            "indd", "indt", "idmi",
                                            "psd", "ai", "raw", "arw",
                                            "cr", "rw2", "nrw", "k25"})) {}

const std::vector<QString>& FileOperation::GetPicturesFileExt() const {
    return mPictures.mFileExtensions;
}

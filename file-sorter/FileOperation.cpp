#include "FileOperation.hpp"

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h" // for stringify JSON
#include <fstream>
#include <iostream>

FileOperation::FileOperation()
    : mPictures(FileOperation::FileSortSettings({"jpg",
                                                 "jpeg",
                                                 "jfi",
                                                 "jpe",
                                                 "jif",
                                                 "jfif",
                                                 "heif",
                                                 "heic",
                                                 "png",
                                                 "gif",
                                                 "svg",
                                                 "svgz"
                                                 "eps",
                                                 "webp",
                                                 "tiff",
                                                 "tif",
                                                 "ind",
                                                 "indd",
                                                 "indt",
                                                 "idmi",
                                                 "psd",
                                                 "ai",
                                                 "raw",
                                                 "arw",
                                                 "cr",
                                                 "rw2",
                                                 "nrw",
                                                 "k25"})) {}

FileOperation::FileSortSettings *
FileOperation::GetFileSortSettings(const Category aCategory) {
  switch (aCategory) {
  case Category::Picture:
    return &mPictures;
  case Category::Video:
    return &mVideos;
  case Category::Audio:
    return &mAudio;
  case Category::Document:
    return &mDocuments;
  default:
    return &mOther;
  }
}

const FileOperation::FileSortSettings &
FileOperation::GetConstantFileSortSettings(const Category aCategory) const {
  switch (aCategory) {
  case Category::Picture:
    return mPictures;
  case Category::Video:
    return mVideos;
  case Category::Audio:
    return mAudio;
  case Category::Document:
    return mDocuments;
  default:
    return mOther;
  }
}

QString
FileOperation::GetCategoryString(const FileOperation::Category aCategory) {
  switch (aCategory) {
  case FileOperation::Category::Picture:
    return "Picture";
  case FileOperation::Category::Video:
    return "Video";
  case FileOperation::Category::Document:
    return "Documents";
  case FileOperation::Category::Audio:
    return "Audio";
  case FileOperation::Category::Other:
    return "Other";
  default:
    return "";
  }
}

const std::vector<QString> &
FileOperation::GetFileExt(const Category aCategory) const {
  return GetConstantFileSortSettings(aCategory).mFileExtensions;
}

const std::vector<FileOperation::DirectoryOutput> &
FileOperation::GetInputDirectories(Category aCategory) const {
  return GetConstantFileSortSettings(aCategory).mInputDirectories;
}

const std::vector<QString> *
FileOperation::GetOutputDirectories(const Category aCategory,
                                    const size_t aIndex) const {
  if (const auto fileSettings = GetConstantFileSortSettings(aCategory);
      aIndex < fileSettings.mInputDirectories.size()) {
    return &GetConstantFileSortSettings(aCategory)
                .mInputDirectories[aIndex]
                .mFolderOutputs;
  }
  return nullptr;
}

std::vector<FileOperation::DirectoryOutput> *
FileOperation::GetInputDirectory(Category aCategory) {
  return &GetFileSortSettings(aCategory)->mInputDirectories;
}

QString FileOperation::GetOutputDestinantion(Category aCategory) const {
  return GetConstantFileSortSettings(aCategory).mOutputDestination;
}

void FileOperation::AddFileExt(Category aCategory, QString aPath) {
  auto fileSortSettings = GetFileSortSettings(aCategory);
  fileSortSettings->mFileExtensions.insert(
      fileSortSettings->mFileExtensions.begin(), aPath);
}

int FileOperation::AddFileInputPath(Category aCategory, QString aPath) {
  int returnIndex = 0;
  auto inputDirectory = GetInputDirectory(aCategory);
  // Check to see if we already have the input directory in the list
  auto it = find_if(inputDirectory->begin(), inputDirectory->end(),
                    [&aPath](const DirectoryOutput &obj) {
                      return obj.mFolderInput == aPath;
                    });
  if (it != inputDirectory->end()) {
    // Input entry found return the index.
    returnIndex = std::distance(inputDirectory->begin(), it);
  } else {
    // Existing entry not found insert path.
    inputDirectory->insert(it,
                           FileOperation::DirectoryOutput{false, false, aPath});
  }
  return returnIndex;
}

int FileOperation::AddSpecificOuputPath(const Category aCategory,
                                        const size_t aIndex, QString aPath) {
  int returnIndex = 0;
  if (FileOperation::FileSortSettings *fileSettings =
          GetFileSortSettings(aCategory);
      aIndex < fileSettings->mInputDirectories.size()) {
    auto outputPaths = &fileSettings->mInputDirectories[aIndex].mFolderOutputs;
    // Check to see if we already have the output directory in the list
    auto it = find_if(outputPaths->begin(), outputPaths->end(),
                      [&aPath](const QString &memberString) {
                        return memberString == aPath;
                      });
    if (it != outputPaths->end()) {
      // Input entry found return the index.
      returnIndex = std::distance(outputPaths->begin(), it);
    } else {
      // Existing entry not found insert path.
      outputPaths->insert(it, aPath);
    }
  }
  return returnIndex;
}

void FileOperation::RemoveFileInputPath(const Category aCategory,
                                        const size_t aIndex) {
  if (auto fileSortSettings = GetFileSortSettings(aCategory);
      aIndex < fileSortSettings->mInputDirectories.size()) {
    fileSortSettings->mInputDirectories.erase(
        std::next(fileSortSettings->mInputDirectories.begin(), aIndex));
  }
}

void FileOperation::RemoveFileExt(const Category aCategory,
                                  const size_t aIndex) {
  if (auto fileSortSettings = GetFileSortSettings(aCategory);
      aIndex < fileSortSettings->mFileExtensions.size()) {
    fileSortSettings->mFileExtensions.erase(
        std::next(fileSortSettings->mFileExtensions.begin(), aIndex));
  }
}

void FileOperation::SetAllFileTypes(const Category aCategory,
                                    const bool aIsAllTypes) {
  GetFileSortSettings(aCategory)->mIsAllFileTypes = aIsAllTypes;
}

void FileOperation::SetDateSorted(const Category aCategory, const size_t aIndex,
                                  const bool aIsDateSorted) {
  if (aIndex < GetFileSortSettings(aCategory)->mInputDirectories.size()) {
    GetFileSortSettings(aCategory)->mInputDirectories[aIndex].mIsDateSort =
        aIsDateSorted;
  }
}

void FileOperation::SetFileComment(const Category aCategory,
                                   const bool aIsFileComment) {
  GetFileSortSettings(aCategory)->mIsFileComment = aIsFileComment;
}

void FileOperation::SetOutputDestinantion(const Category aCategory,
                                          QString aOutputDestination) {
  GetFileSortSettings(aCategory)->mOutputDestination = aOutputDestination;
}

void FileOperation::SetMultiDestination(const Category aCategory,
                                        const size_t aIndex,
                                        const bool aIsMultiDestination) {
  if (auto *fileSortSettings = GetFileSortSettings(aCategory);
      aIndex < fileSortSettings->mInputDirectories.size())
    fileSortSettings->mInputDirectories[aIndex].mIsMultiDestination =
        aIsMultiDestination;
}

bool FileOperation::IsMultiDestination(const Category aCategory,
                                       size_t aIndex) {
  if (const auto *fileSortSettings = GetFileSortSettings(aCategory);
      fileSortSettings && aIndex < fileSortSettings->mInputDirectories.size()) {
    return fileSortSettings->mInputDirectories[aIndex].mIsMultiDestination;
  }
  return false;
}

bool FileOperation::IsDateSort(const Category aCategory, const size_t aIndex) {
  if (aIndex < GetFileSortSettings(aCategory)->mInputDirectories.size()) {
    return GetFileSortSettings(aCategory)
        ->mInputDirectories[aIndex]
        .mIsDateSort;
  }
  return false;
}

bool FileOperation::IsFileComment(const Category aCategory) {
  return GetFileSortSettings(aCategory)->mIsFileComment;
}

bool FileOperation::IsAllFileTypes(const Category aCategory) {
  return GetFileSortSettings(aCategory)->mIsAllFileTypes;
}

bool FileOperation::SaveConfiguration(const QString aFilePath) {
  std::ofstream saveFile(aFilePath.toStdString());
  rapidjson::StringBuffer outputString;
  rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(outputString);

  if (!saveFile) {
    // Display error message.
    return false;
  }
  writer.StartObject();
  for (auto category : AllCategories) {
    auto fileSortSettings = GetConstantFileSortSettings(category);
    const auto categoryString = GetCategoryString(category).toStdString();
    auto writeJsonKey = [&writer,
                         &categoryString](const std::string aRightString) {
      const std::string keyString = categoryString + aRightString;
      writer.Key(keyString.c_str(), keyString.size());
    };
    writeJsonKey("DirectoryOutputs");
    writer.StartArray();
    for (int i = 0; 0 < fileSortSettings.mInputDirectories.size(); i++) {
      writeJsonKey("IsMultiDestination");
      writer.Bool(fileSortSettings.mInputDirectories[i].mIsMultiDestination);
      writeJsonKey("IsDateSorted");
      writer.Bool(fileSortSettings.mInputDirectories[i].mIsDateSort);
      writeJsonKey("FolderInput");
      writer.String(fileSortSettings.mInputDirectories[i]
                        .mFolderInput.toStdString()
                        .c_str(),
                    fileSortSettings.mInputDirectories[i].mFolderInput.size());
      writeJsonKey("FolderOutputs");
      writer.StartArray();
      for (int j = 0;
           j < fileSortSettings.mInputDirectories[i].mFolderOutputs.size();
           j++) {
        writer.String(
            fileSortSettings.mInputDirectories[i]
                .mFolderOutputs[j]
                .toStdString()
                .c_str(),
            fileSortSettings.mInputDirectories[i].mFolderOutputs[j].size());
      }
      writer.EndArray();
    }
    writer.EndArray();
    writeJsonKey("FileExtensions");
    writer.StartArray();
    for (int i = 0; i < fileSortSettings.mFileExtensions.size(); i++) {
      writer.String(fileSortSettings.mFileExtensions[i].toStdString().c_str(),
                    fileSortSettings.mFileExtensions[i].size());
    }
    writer.EndArray();
    writeJsonKey("OutputDestination");
    writer.String(fileSortSettings.mOutputDestination.toStdString().c_str(),
                  fileSortSettings.mOutputDestination.size());
    writeJsonKey("IsFileComment");
    writer.Bool(fileSortSettings.mIsFileComment);
    writeJsonKey("IsAllFileTypes");
    writer.Bool(fileSortSettings.mIsAllFileTypes);
  }
  writer.Key("OutputDestination");
  writer.String(mOutputDestination.toStdString().c_str(),
                mOutputDestination.size());
  writer.EndObject();

  saveFile << outputString.GetString();
  saveFile.close();

  return true;
}

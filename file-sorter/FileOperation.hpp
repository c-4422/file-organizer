#ifndef FILEOPERATION_HPP
#define FILEOPERATION_HPP

#include <QString>
#include <vector>

class FileOperation {
public:
  struct DirectoryOutput {
    bool mIsMultiDestination = false;
    QString mFolderInput{};
    std::vector<QString> mFolderOutputs{};
  };
  enum Category { Picture, Video, Audio, Document, Other };

  FileOperation();

  const std::vector<QString> &GetFileExt(Category aCategory) const;
  const std::vector<DirectoryOutput> &
  GetInputDirectories(Category aCategory) const;
  const std::vector<QString> &GetOutputDirectories(Category aCategory,
                                                   size_t aIndex) const;
  QString GetOutputDestinantion() const;
  QString GetOutputDestinantion(Category aCategory) const;
  void SetOutputDestinantion(QString aOutputDestination);
  void SetOutputDestinantion(Category aCategory, QString aOutputDestination);
  void AddFileExt(Category aCategory, QString aString);
  int AddFileInputPath(Category aCategory, QString aString);
  int AddSpecificOuputPath(Category aCategory, size_t aIndex, QString aString);
  void RemoveFileInputPath(Category aCategory, size_t aIndex);
  void RemoveFileExt(Category aCategory, size_t aIndex);
  void SetAllFileTypes(Category aCategory, bool aIsAllTypes);
  void SetDateSorted(Category aCategory, bool aIsDateSorted);
  void SetFileComment(Category aCategory, bool aIsFileComment);
  void SetMultiDestination(Category aCategory, size_t aIndex,
                           bool aIsMultiDestination);

private:
  struct FileSortSettings {
    FileSortSettings(std::vector<QString> aFileExtensions)
        : mFileExtensions(aFileExtensions) {}
    FileSortSettings() {}

    std::vector<DirectoryOutput> mInputDirectories{};
    std::vector<QString> mFileExtensions{};
    QString mOutputDestination{};
    bool mIsDateSort = false;
    bool mIsFileComment = false;
    bool mIsAllFileTypes = false;
  };
  FileSortSettings *GetFileSortSettings(Category aCategory);
  const FileSortSettings &GetConstantFileSortSettings(Category aCategory) const;
  std::vector<DirectoryOutput> *GetInputDirectory(const Category aCategory);

  QString mOutputDestination{};
  FileSortSettings mPictures;
  FileSortSettings mVideos;
  FileSortSettings mAudio;
  FileSortSettings mDocuments;
  FileSortSettings mOther;
};

inline QString FileOperation::GetOutputDestinantion() const {
  return mOutputDestination;
}

inline void FileOperation::SetOutputDestinantion(QString aOutputDestination) {
  mOutputDestination = aOutputDestination;
}

#endif // FILEOPERATION_HPP

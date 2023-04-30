#ifndef FILEOPERATION_HPP
#define FILEOPERATION_HPP

#include <QString>
#include <vector>

class FileOperation {
public:
  struct DirectoryOutput {
    QString mFolderInput{};
    std::vector<QString> mFolderOutputs{};
  };
  enum Category {
    Picture,
    Video,
    Music,
    Document,
    Other
  };

  FileOperation();

  const std::vector<QString>& GetFileExt(Category aCategory) const;
  const std::vector<DirectoryOutput>& GetInputDirectories(Category aCategory) const;
  QString GetOutputDestinantion() const;
  QString GetOutputDestinantion(Category aCategory) const;
  void SetOutputDestinantion(QString aOutputDestination);
  void SetOutputDestinantion(Category aCategory, QString aOutputDestination);
  void AddFileExt(Category aCategory, QString aString);
  int AddFileInputPath(Category aCategory, QString aString);
  void RemoveFileExt(Category aCategory, int aIndex);
  void SetAllFileTypes(Category aCategory, bool aIsAllTypes);
  void SetDateSorted(Category aCategory, bool aIsDateSorted);
  void SetFileComment(Category aCategory, bool aIsFileComment);

private:
  struct FileSortSettings {
    FileSortSettings(std::vector<QString> aFileExtensions):
      mFileExtensions(aFileExtensions) {}
    FileSortSettings() {}

    std::vector<DirectoryOutput> mInputDirectories{};
    std::vector<QString> mFileExtensions{};
    QString mOutputDestination{};
    bool mIsDateSort = false;
    bool mIsFileComment = false;
    bool mIsAllFileTypes = false;
    bool mIsMultiDestination = false;
  };
  std::vector<DirectoryOutput>& GetInputDirectory(Category aCategory);

  QString mOutputDestination{};
  FileSortSettings mPictures;
  FileSortSettings mVideos;
  FileSortSettings mMusic;
  FileSortSettings mDocuments;
  FileSortSettings mOther;
};

inline QString FileOperation::GetOutputDestinantion() const { return mOutputDestination; }

inline void FileOperation::SetOutputDestinantion(QString aOutputDestination) {
  mOutputDestination = aOutputDestination;
}

#endif // FILEOPERATION_HPP

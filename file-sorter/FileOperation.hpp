#ifndef FILEOPERATION_HPP
#define FILEOPERATION_HPP

#include <QString>
#include <optional>
#include <vector>

class FileOperation {
public:
  enum class Category : int { Picture, Video, Audio, Document, Other, Invalid };

  struct DirectoryOutput {
    bool mIsMultiDestination = false;
    bool mIsDateSort = false;
    QString mFolderInput{};
    std::vector<QString> mFolderOutputs{};
  };

  static constexpr std::initializer_list AllCategories = {
      Category::Picture, Category::Video, Category::Audio, Category::Document,
      Category::Other};

  FileOperation();

  static QString GetCategoryString(FileOperation::Category aCategory);
  const std::vector<QString> &GetFileExt(Category aCategory) const;
  const std::vector<DirectoryOutput> &
  GetInputDirectories(Category aCategory) const;
  const std::vector<QString> *GetOutputDirectories(Category aCategory,
                                                   size_t aIndex) const;
  QString GetOutputDestinantion() const;
  QString GetConfigurationFilePath() const;
  QString GetOutputDestinantion(Category aCategory) const;
  void SetOutputDestinantion(QString aOutputDestination);
  void SetOutputDestinantion(Category aCategory, QString aOutputDestination);
  void AddFileExt(Category aCategory, QString aPath);
  int AddFileInputPath(Category aCategory, QString aPath);
  int AddSpecificOuputPath(Category aCategory, size_t aIndex, QString aPath);
  void RemoveFileInputPath(Category aCategory, size_t aIndex);
  void RemoveFileExt(Category aCategory, size_t aIndex);
  void SetAllFileTypes(Category aCategory, bool aIsAllTypes);
  void SetDateSorted(Category aCategory, size_t aIndex, bool aIsDateSorted);
  void SetFileComment(Category aCategory, bool aIsFileComment);
  void SetMultiDestination(Category aCategory, size_t aIndex,
                           bool aIsMultiDestination);
  bool IsMultiDestination(Category aCategory, size_t aIndex);
  bool IsDateSort(Category aCategory, size_t aIndex);
  bool IsFileComment(Category aCategory);
  bool IsAllFileTypes(Category aCategory);
  bool SaveConfiguration(QString aFilePath);

private:
  struct FileSortSettings {
    FileSortSettings(std::vector<QString> aFileExtensions)
        : mFileExtensions(aFileExtensions) {}
    FileSortSettings() {}

    std::vector<DirectoryOutput> mInputDirectories{};
    std::vector<QString> mFileExtensions{};
    QString mOutputDestination{};
    bool mIsFileComment = false;
    bool mIsAllFileTypes = false;
  };
  FileSortSettings *GetFileSortSettings(Category aCategory);
  const FileSortSettings &GetConstantFileSortSettings(Category aCategory) const;
  std::vector<DirectoryOutput> *GetInputDirectory(const Category aCategory);

  QString mOutputDestination{};
  QString mOpenConfigurationFile{};
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

inline QString FileOperation::GetConfigurationFilePath() const {
  return mOpenConfigurationFile;
}

#endif // FILEOPERATION_HPP

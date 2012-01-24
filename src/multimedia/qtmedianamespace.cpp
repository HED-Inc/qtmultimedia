/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the documentation of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:FDL$
** GNU Free Documentation License
** Alternatively, this file may be used under the terms of the GNU Free
** Documentation License version 1.3 as published by the Free Software
** Foundation and appearing in the file included in the packaging of
** this file.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms
** and conditions contained in a signed written agreement between you
** and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qtmedianamespace.h"

QT_BEGIN_NAMESPACE

/*!
    \namespace QtMultimedia
    \ingroup multimedia
    \inmodule QtMultimedia

    \ingroup multimedia
    \ingroup multimedia_core

    \brief The QtMultimedia namespace contains miscellaneous identifiers used throughout the Qt Media services library.

    QtMultimedia is a module containing the low level, low latency,
    Multimedia APIs which were introduced in Qt 4.6 and also includes the
    high level QtMultimedia APIs which were introduced in QtMobility 1.0.

*/

namespace
{
    class QMultimediaNamespacePrivateRegisterMetaTypes
    {
    public:
        QMultimediaNamespacePrivateRegisterMetaTypes()
        {
            qRegisterMetaType<QtMultimedia::AvailabilityError>();
            qRegisterMetaType<QtMultimedia::SupportEstimate>();
            qRegisterMetaType<QtMultimedia::EncodingMode>();
            qRegisterMetaType<QtMultimedia::EncodingQuality>();
        }
    } _registerMetaTypes;
}

/*
    When these conditions are satisfied, QStringLiteral is implemented by
    gcc's statement-expression extension.  However, in this file it will
    not work, because "statement-expressions are not allowed outside functions
    nor in template-argument lists".

    Fall back to the less-performant QLatin1String in this case.
*/
#if defined(QStringLiteral) && defined(QT_UNICODE_LITERAL_II) && defined(Q_CC_GNU) && !defined(Q_COMPILER_LAMBDA)
# undef QStringLiteral
# define QStringLiteral QLatin1String
#endif

#define Q_DEFINE_METADATA(key) const QString QtMultimedia::MetaData::key(QStringLiteral(#key))

// Common
Q_DEFINE_METADATA(Title);
Q_DEFINE_METADATA(SubTitle);
Q_DEFINE_METADATA(Author);
Q_DEFINE_METADATA(Comment);
Q_DEFINE_METADATA(Description);
Q_DEFINE_METADATA(Category);
Q_DEFINE_METADATA(Genre);
Q_DEFINE_METADATA(Year);
Q_DEFINE_METADATA(Date);
Q_DEFINE_METADATA(UserRating);
Q_DEFINE_METADATA(Keywords);
Q_DEFINE_METADATA(Language);
Q_DEFINE_METADATA(Publisher);
Q_DEFINE_METADATA(Copyright);
Q_DEFINE_METADATA(ParentalRating);
Q_DEFINE_METADATA(RatingOrganization);

// Media
Q_DEFINE_METADATA(Size);
Q_DEFINE_METADATA(MediaType);
Q_DEFINE_METADATA(Duration);

// Audio
Q_DEFINE_METADATA(AudioBitRate);
Q_DEFINE_METADATA(AudioCodec);
Q_DEFINE_METADATA(AverageLevel);
Q_DEFINE_METADATA(ChannelCount);
Q_DEFINE_METADATA(PeakValue);
Q_DEFINE_METADATA(SampleRate);

// Music
Q_DEFINE_METADATA(AlbumTitle);
Q_DEFINE_METADATA(AlbumArtist);
Q_DEFINE_METADATA(ContributingArtist);
Q_DEFINE_METADATA(Composer);
Q_DEFINE_METADATA(Conductor);
Q_DEFINE_METADATA(Lyrics);
Q_DEFINE_METADATA(Mood);
Q_DEFINE_METADATA(TrackNumber);
Q_DEFINE_METADATA(TrackCount);

Q_DEFINE_METADATA(CoverArtUrlSmall);
Q_DEFINE_METADATA(CoverArtUrlLarge);

// Image/Video
Q_DEFINE_METADATA(Resolution);
Q_DEFINE_METADATA(PixelAspectRatio);

// Video
Q_DEFINE_METADATA(VideoFrameRate);
Q_DEFINE_METADATA(VideoBitRate);
Q_DEFINE_METADATA(VideoCodec);

Q_DEFINE_METADATA(PosterUrl);

// Movie
Q_DEFINE_METADATA(ChapterNumber);
Q_DEFINE_METADATA(Director);
Q_DEFINE_METADATA(LeadPerformer);
Q_DEFINE_METADATA(Writer);

// Photos
Q_DEFINE_METADATA(CameraManufacturer);
Q_DEFINE_METADATA(CameraModel);
Q_DEFINE_METADATA(Event);
Q_DEFINE_METADATA(Subject);
Q_DEFINE_METADATA(Orientation);
Q_DEFINE_METADATA(ExposureTime);
Q_DEFINE_METADATA(FNumber);
Q_DEFINE_METADATA(ExposureProgram);
Q_DEFINE_METADATA(ISOSpeedRatings);
Q_DEFINE_METADATA(ExposureBiasValue);
Q_DEFINE_METADATA(DateTimeOriginal);
Q_DEFINE_METADATA(DateTimeDigitized);
Q_DEFINE_METADATA(SubjectDistance);
Q_DEFINE_METADATA(MeteringMode);
Q_DEFINE_METADATA(LightSource);
Q_DEFINE_METADATA(Flash);
Q_DEFINE_METADATA(FocalLength);
Q_DEFINE_METADATA(ExposureMode);
Q_DEFINE_METADATA(WhiteBalance);
Q_DEFINE_METADATA(DigitalZoomRatio);
Q_DEFINE_METADATA(FocalLengthIn35mmFilm);
Q_DEFINE_METADATA(SceneCaptureType);
Q_DEFINE_METADATA(GainControl);
Q_DEFINE_METADATA(Contrast);
Q_DEFINE_METADATA(Saturation);
Q_DEFINE_METADATA(Sharpness);
Q_DEFINE_METADATA(DeviceSettingDescription);

Q_DEFINE_METADATA(PosterImage);
Q_DEFINE_METADATA(CoverArtImage);
Q_DEFINE_METADATA(ThumbnailImage);


/*!
    \namespace QtMultimedia::MetaData

    This namespace provides identifiers for meta-data attributes.

    \note Not all identifiers are supported on all platforms. Please consult vendor documentation for specific support
    on different platforms.

    Common attributes
    \value Title The title of the media.  QString.
    \value SubTitle The sub-title of the media. QString.
    \value Author The authors of the media. QStringList.
    \value Comment A user comment about the media. QString.
    \value Description A description of the media.  QString
    \value Category The category of the media.  QStringList.
    \value Genre The genre of the media.  QStringList.
    \value Year The year of release of the media.  int.
    \value Date The date of the media. QDate.
    \value UserRating A user rating of the media. int [0..100].
    \value Keywords A list of keywords describing the media.  QStringList.
    \value Language The language of media, as an ISO 639-2 code.

    \value Publisher The publisher of the media.  QString.
    \value Copyright The media's copyright notice.  QString.
    \value ParentalRating  The parental rating of the media.  QString.
    \value RatingOrganization The organization responsible for the parental rating of the media.
    QString.

    Media attributes
    \value Size The size in bytes of the media. qint64
    \value MediaType The type of the media (audio, video, etc).  QString.
    \value Duration The duration in millseconds of the media.  qint64.

    Audio attributes
    \value AudioBitRate The bit rate of the media's audio stream in bits per second.  int.
    \value AudioCodec The codec of the media's audio stream.  QString.
    \value AverageLevel The average volume level of the media.  int.
    \value ChannelCount The number of channels in the media's audio stream. int.
    \value PeakValue The peak volume of the media's audio stream. int
    \value SampleRate The sample rate of the media's audio stream in hertz. int

    Music attributes
    \value AlbumTitle The title of the album the media belongs to.  QString.
    \value AlbumArtist The principal artist of the album the media belongs to.  QString.
    \value ContributingArtist The artists contributing to the media.  QStringList.
    \value Composer The composer of the media.  QStringList.
    \value Conductor The conductor of the media. QString.
    \value Lyrics The lyrics to the media. QString.
    \value Mood The mood of the media.  QString.
    \value TrackNumber The track number of the media.  int.
    \value TrackCount The number of tracks on the album containing the media.  int.

    \value CoverArtUrlSmall The URL of a small cover art image. QUrl.
    \value CoverArtUrlLarge The URL of a large cover art image. QUrl.
    \value CoverArtImage An embedded cover art image. QImage.

    Image and video attributes
    \value Resolution The dimensions of an image or video.  QSize.
    \value PixelAspectRatio The pixel aspect ratio of an image or video.  QSize.

    Video attributes
    \value VideoFrameRate The frame rate of the media's video stream.  qreal.
    \value VideoBitRate The bit rate of the media's video stream in bits per second.  int.
    \value VideoCodec The codec of the media's video stream.  QString.

    \value PosterUrl The URL of a poster image.  QUrl.
    \value PosterImage An embedded poster image.  QImage.

    Movie attributes
    \value ChapterNumber The chapter number of the media.  int.
    \value Director The director of the media.  QString.
    \value LeadPerformer The lead performer in the media.  QStringList.
    \value Writer The writer of the media.  QStringList.

    Photo attributes.
    \value CameraManufacturer The manufacturer of the camera used to capture the media.  QString.
    \value CameraModel The model of the camera used to capture the media.  QString.
    \value Event The event during which the media was captured.  QString.
    \value Subject The subject of the media.  QString.
    \value Orientation Orientation of image.
    \value ExposureTime Exposure time, given in seconds.
    \value FNumber The F Number.
    \value ExposureProgram
        The class of the program used by the camera to set exposure when the picture is taken.
    \value ISOSpeedRatings
        Indicates the ISO Speed and ISO Latitude of the camera or input device as specified in ISO 12232.
    \value ExposureBiasValue
        The exposure bias.
        The unit is the APEX (Additive System of Photographic Exposure) setting.
    \value DateTimeOriginal The date and time when the original image data was generated.
    \value DateTimeDigitized The date and time when the image was stored as digital data.
    \value SubjectDistance The distance to the subject, given in meters.
    \value MeteringMode The metering mode.
    \value LightSource
        The kind of light source.
    \value Flash
        Status of flash when the image was shot.
    \value FocalLength
        The actual focal length of the lens, in mm.
    \value ExposureMode
        Indicates the exposure mode set when the image was shot.
    \value WhiteBalance
        Indicates the white balance mode set when the image was shot.
    \value DigitalZoomRatio
        Indicates the digital zoom ratio when the image was shot.
    \value FocalLengthIn35mmFilm
        Indicates the equivalent focal length assuming a 35mm film camera, in mm.
    \value SceneCaptureType
        Indicates the type of scene that was shot.
        It can also be used to record the mode in which the image was shot.
    \value GainControl
        Indicates the degree of overall image gain adjustment.
    \value Contrast
        Indicates the direction of contrast processing applied by the camera when the image was shot.
    \value Saturation
        Indicates the direction of saturation processing applied by the camera when the image was shot.
    \value Sharpness
        Indicates the direction of sharpness processing applied by the camera when the image was shot.
    \value DeviceSettingDescription
        Exif tag, indicates information on the picture-taking conditions of a particular camera model. QString

    \value ThumbnailImage An embedded thumbnail image.  QImage.
*/

/*!
    \enum QtMultimedia::SupportEstimate

    Enumerates the levels of support a media service provider may have for a feature.

    \value NotSupported The feature is not supported.
    \value MaybeSupported The feature may be supported.
    \value ProbablySupported The feature is probably supported.
    \value PreferredService The service is the preferred provider of a service.
*/

/*!
    \enum QtMultimedia::EncodingQuality

    Enumerates quality encoding levels.

    \value VeryLowQuality
    \value LowQuality
    \value NormalQuality
    \value HighQuality
    \value VeryHighQuality
*/

/*!
    \enum QtMultimedia::EncodingMode

    Enumerates encoding modes.

    \value ConstantQualityEncoding
    \value ConstantBitRateEncoding
    \value AverageBitRateEncoding
    \value TwoPassEncoding
*/

/*!
    \enum QtMultimedia::AvailabilityError

    Enumerates Service status errors.

    \value NoError The service is operating correctly.
    \value ServiceMissingError There is no service available to provide the requested functionality.
    \value ResourceError The service could not allocate resources required to function correctly.
    \value BusyError The service must wait for access to necessary resources.
*/

QT_END_NAMESPACE

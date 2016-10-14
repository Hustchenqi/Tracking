#ifndef TRACKER_MANAGER_H
#define TRACKER_MANAGER_H
#include "regressor_base.h"
#include "regressor.h"
#include "tracker.h"
#include "high_res_timer.h"

// Manage the iteration over all videos and tracking the objects inside.
class TrackerManager
{
public:
  TrackerManager(const cv::Mat& frame,
                 RegressorBase* regressor, Tracker* tracker);

  // Iterate over all videos and track the target object in each.
  void TrackAll() ;

  // Iterate over all videos and track the target object in each.
  // Start tracking the video with index start_video_num (for debugging).
  // pause_val is normally ignored.
  void TrackAll(const size_t start_video_num, const int pause_val);

  // Functions for subclasses that get called at appropriate times.
  virtual void VideoInit(const Video& video, const size_t video_num) {}

  // Called immediately before estimating the current location of the target object.
  virtual void SetupEstimate() {}

  // Called immediately after estimating the current location of the target object.
  virtual void ProcessTrackOutput(
      const size_t frame_num, const cv::Mat& image_curr, const bool has_annotation,
      const BoundingBox& bbox_gt, const BoundingBox& bbox_estimate_uncentered,
      const int pause_val) {}

protected:
  // Videos to track.
  cv::Mat frame;

  // Neural network tracker.
  RegressorBase* regressor_;

  // Tracker.
  Tracker* tracker_;
};

// Track objects and visualize the tracker output.
class TrackerVisualizer : public TrackerManager
{
public:
  TrackerVisualizer(const std::vector<Video>& videos,
                    RegressorBase* regressor, Tracker* tracker);

  // Print which video is being visualized.
  virtual void VideoInit(const Video& video, const size_t video_num);

  // Show the tracking estimate and the ground-truth target location.
  virtual void ProcessTrackOutput(
      const size_t frame_num, const cv::Mat& image_curr, const bool has_annotation,
      const BoundingBox& bbox_gt, const BoundingBox& bbox_estimate,
      const int pause_val);
};

#endif // TRACKER_MANAGER_H

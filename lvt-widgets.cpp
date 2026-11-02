// ==WindhawkMod==
// @id              lvt-widgets
// @name            LVT Widgets
// @description     Liquid glass desktop widgets for Windows 11: weather, calendar, clock, RSS headlines, countdown, Pomodoro, and timer. GPU-rendered glass, drag-and-snap layout, and per-widget settings.
// @version         1.0.0
// @author          LVT
// @github          https://github.com/lamvt-stack
// @include         windhawk.exe
// @compilerOptions -DWIN32_LEAN_AND_MEAN -ldwmapi -lgdiplus -lgdi32 -lole32 -luuid -lshell32 -ladvapi32 -ld3d11 -ldxgi -ld3dcompiler
// @license         MIT
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# LVT Widgets 1.0.0

Liquid glass desktop widgets for Windows 11: weather, calendar, clock, RSS headlines, countdown, Pomodoro, and timer. Drag widgets anywhere; they snap to screen edges and to each other.

## Widgets

| Widget | Size | Shows |
|---|---|---|
| Weather | 275 px wide | Current conditions, high and low, and the next hours. Hourly, five-day, and extended layouts. |
| Calendar | 145 × 145 or 275 px wide | Month, upcoming events, weekly agenda, or today. Reads a Google Calendar iCal address. |
| Clock | 145 × 145 or 275 × 145 | Analog, digital, city, world grid, or world list. Dark, glass, or light style. |
| RSS headlines | 275 px wide | Headlines from any RSS or Atom feed. Click a headline to open it. |
| Countdown | 145 × 145 | Time left until a date and time. |
| Pomodoro | 145 × 145 | Focus and break cycles. |
| Timer | 275 × 145 | 5, 10, or 15 minute, or custom countdown. |

## Setup

- **Weather:** works without a key. Set your latitude and longitude.
- **Calendar:** in Google Calendar, open Settings, pick your calendar, and copy *Secret address in iCal format* into the calendar address setting. Treat it like a password.
- **RSS:** paste any RSS or Atom feed address.
- **Countdown:** enter the target as `YYYY-MM-DD HH:MM` in local time.
- **Clock cities:** each entry is `code|Name|Windows time zone`, separated by semicolons. Run `tzutil /l` to list time zone names.

## Controls

- **Drag** a widget to move it. Drop it near a screen edge or another widget to snap, leaving the gap set in settings.
- **Click** the weather or calendar widget to refresh its data.
- **RSS:** use the mouse wheel or the scrollbar. Click a headline to open it.
- **Pomodoro:** click the centre of the ring to start or pause. Right-click to reset.
- **Timer:** Start, Stop, and Reset buttons. Pick a preset or Custom at any time; a running timer stops and takes the new length.
- **Countdown:** display only.

## Performance

- Weather, calendar, and RSS each fetch on their own background thread, at the interval you set.
- Glass is rendered on the GPU (Direct3D 11) and reused until the wallpaper, size, or glass settings change. A CPU fallback is available.
- Only the area covered by widgets is redrawn and presented.
- One timer ticks each second, and only while a seconds display or countdown is enabled.

## Troubleshooting

- **Glass looks wrong or widgets are blank:** set *Glass rendering* to CPU to check. Then look for Direct3D messages in the Windhawk log.
- **No notification when a timer ends:** Focus Assist (Win + N) can hide balloons.
- **Calendar or RSS is empty:** check the address. The Windhawk log shows *Calendar loaded* or *RSS loaded* on success.
- **Wallpaper behind the glass is out of date:** it updates within a few seconds of a change, and after a display change.

## Requirements

Windows 11 (built for 25H2). Direct3D 11 for GPU glass; CPU glass works without it.

## Release notes 1.0.0

- First stable release.
- Consistent header row and glass style across all widgets.
- GPU glass is cached and reused, and only changed areas are redrawn.
- Widgets blend correctly where they overlap.
- Settings grouped by widget. Existing settings keep their names and values.
- Timer presets can be chosen while running.
- Pomodoro starts and pauses from the centre of its ring, so the rest of the widget can still be dragged.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
# ── Weather ──
- showWeather: true
  $name: Show weather widget

- locationLabel: Danville, CA 94526
  $name: Weather location label
  $description: Shown at the top of the weather widget

- latitude: "37.8136"
  $name: Weather latitude
  $description: Danville, CA 94526 (ZIP code centroid).

- longitude: "-121.9978"
  $name: Weather longitude

- temperatureUnits: fahrenheit
  $name: Temperature units
  $options:
    - fahrenheit: Fahrenheit
    - celsius: Celsius

- weatherLayout: current
  $name: Weather layout
  $options:
    - current: Current conditions + hourly
    - day: 1-day summary (High, Low, Precip, Wind)
    - extended: Hourly + 5-day forecast

- weatherSize: medium
  $name: Weather widget size
  $options:
    - small: Small
    - medium: Medium
    - large: Large

- weatherRefreshMinutes: 15
  $name: Weather refresh interval (minutes)
  $description: From 5 to 240.

# ── Calendar ──
- showCalendar: true
  $name: Show calendar widget

- calendarLayout: month
  $name: Calendar layout
  $options:
    - month: Month
    - upcoming: Upcoming events and month
    - agenda: Weekly agenda
    - today: Today

- calendarSize: medium
  $name: Calendar widget size
  $description: Applies to the month and today layouts. The upcoming and agenda layouts are wider.
  $options:
    - small: Small
    - medium: Medium
    - large: Large

- calendarUrl: ""
  $name: Google Calendar secret iCal address
  $description: In Google Calendar, open Settings, choose your calendar, and copy "Secret address in iCal format". Treat it like a password.

- calendarStyle: glass
  $name: Calendar style
  $options:
    - glass: Liquid glass
    - dark: Dark

- showEventDots: true
  $name: Show event dots
  $description: Mark days that have events.

- calendarRefreshMinutes: 60
  $name: Calendar refresh interval (minutes)
  $description: From 5 to 1440.

# ── Clock ──
- showClock: true
  $name: Show clock widget

- clockLayout: analog
  $name: Clock layout
  $options:
    - analog: Analog
    - digital: Digital
    - cityAnalog: City analog
    - cityDigital: City digital
    - worldGrid: World grid (2 x 2)
    - worldList: World list

- clockStyle: glass
  $name: Clock style
  $options:
    - dark: Dark
    - glass: Liquid glass
    - light: Light

- clockSize: medium
  $name: Clock widget size
  $description: Applies to the square layouts. The city digital and world list layouts are wide.
  $options:
    - small: Small
    - medium: Medium
    - large: Large

- clockSecondHand: true
  $name: Show second hand
  $description: Updates the clock every second. Turn off to update every 15 seconds.

- clockWorlds: "LAX|Los Angeles|Pacific Standard Time;LON|London|GMT Standard Time;TYO|Tokyo|Tokyo Standard Time;SYD|Sydney|AUS Eastern Standard Time"
  $name: Cities
  $description: Up to four entries, each code|City name|Windows time zone, separated by semicolons. Run "tzutil /l" to list time zone names.

# ── RSS headlines ──
- showRss: true
  $name: Show RSS widget

- rssUrl: "https://www.pbs.org/newshour/feeds/rss/headlines"
  $name: RSS / Atom feed URL
  $description: HTTP or HTTPS feed URL.

- rssMaxItems: 25
  $name: Maximum feed items
  $description: Maximum number of headlines downloaded and retained (1 to 200).

- rssVisibleRows: 6
  $name: Visible headline rows
  $description: Rows shown at once. Remaining downloaded items are available by scrolling (1 to 20).

- rssAutoSize: false
  $name: Size widget to fit all rows
  $description: When enabled, widget height grows to fit all downloaded items, up to the configured maximum.

- rssRefreshMinutes: 15
  $name: RSS refresh interval (minutes)
  $description: From 5 to 240.

- rssTextColor: "#FFFFFF"
  $name: RSS text color (HEX)
  $description: Six-digit HEX color, for example #FFFFFF.

- rssTextShadow: 70
  $name: RSS text shadow intensity (%)
  $description: Subtle black drop shadow behind RSS text. 0 disables it; 100 is strongest.

# ── Countdown ──
- showCountdown: true
  $name: Show countdown widget

- countdownTitle: "Countdown"
  $name: Countdown title
  $description: Shown above the countdown numbers.

- countdownDate: ""
  $name: Countdown target date and time
  $description: Local time in the form YYYY-MM-DD HH:MM, for example 2026-12-25 09:00.

- countdownStyle: glass
  $name: Countdown style
  $options:
    - glass: Liquid glass
    - dark: Dark

# ── Pomodoro ──
- showPomodoro: true
  $name: Show Pomodoro widget
  $description: Click the centre of the ring to start or pause. Right-click to reset.

- pomodoroWorkMinutes: 25
  $name: Focus length (minutes)
  $description: From 1 to 120.

- pomodoroBreakMinutes: 5
  $name: Break length (minutes)
  $description: From 1 to 60.

- pomodoroStyle: glass
  $name: Pomodoro style
  $options:
    - glass: Liquid glass
    - dark: Dark

# ── Timer ──
- showTimer: true
  $name: Show timer widget
  $description: Presets of 5, 10, and 15 minutes, plus a custom length. Start, stop, and reset with the buttons.

- timerCustomMinutes: 30
  $name: Custom timer length (minutes)
  $description: The length used by the Custom button. From 1 to 720.

- timerStyle: glass
  $name: Timer style
  $options:
    - glass: Liquid glass
    - dark: Dark

# ── Glass appearance and animation ──
- glassRendering: gpu
  $name: Glass rendering (weather, calendar and clock)
  $description: GPU uses Direct3D 11 for refraction, blur and lighting. CPU is the simpler fallback.
  $options:
    - gpu: GPU (Direct3D 11)
    - cpu: CPU (GDI+)

- glassBlur: 2
  $name: Backdrop blur (px)
  $description: 0 to 20.

- glassRefraction: 24
  $name: Refraction (px)
  $description: 0 to 30.

- glassBevel: 28
  $name: Edge bevel width (px)
  $description: 4 to 40.

- glassChromatic: 60
  $name: Chromatic dispersion (%)
  $description: 0 to 100.

- glassSpecular: 120
  $name: Specular highlight (%)
  $description: 0 to 200.

- glassSheen: 20
  $name: Sheen strength (%)
  $description: 0 to 100.

- glassSheenWidth: 35
  $name: Sheen band width
  $description: 10 to 100.

- glassRim: 90
  $name: Rim light (%)
  $description: 0 to 150.

- glassGrain: 10
  $name: Surface grain
  $description: 0 to 100.

- glassShadow: 15
  $name: Shadow strength (%)
  $description: Soft shadow under the glass. 0 removes it. 0 to 100.

- glassTintTop: "#1A1F29"
  $name: Tint color (top)
  $description: Hex color, for example #1A1F29

- glassTintTopOpacity: 15
  $name: Tint opacity (top, %)
  $description: 0 to 100.

- glassTintBottom: "#596675"
  $name: Tint color (bottom)
  $description: Hex color, for example #596675

- glassTintBottomOpacity: 30
  $name: Tint opacity (bottom, %)
  $description: 0 to 100.

- sheenAnimation: false
  $name: Animate weather sheen
  $description: Sweeps the sheen band across the weather glass. Uses extra CPU and GPU. Needs GPU rendering.

- sheenPeriod: 8
  $name: Sheen sweep period (seconds)
  $description: 2 to 60.

- animationFps: 30
  $name: Animation frame rate
  $description: 10 to 60.

# ── Layout and snapping ──
- snapDistance: 20
  $name: Edge snap distance (px)
  $description: When a widget is dragged within this many pixels of a screen edge or another widget's edge, it snaps to that edge. 0 turns snapping off. 0 to 200.

- snapGap: 20
  $name: Minimum gap when snapped (px)
  $description: Space left between a snapped widget and the screen border or another widget. 0 snaps flush. 0 to 200.
*/
// ==/WindhawkModSettings==

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <winsock2.h>
#include <windhawk_api.h>

#include <windows.h>
#include <windowsx.h>
#include <objbase.h>
#include <shobjidl.h>
#include <dwmapi.h>
#include <dxgi.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <gdiplus.h>
#include <shellapi.h>

#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cwchar>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

using namespace Gdiplus;

namespace {

// ── Layout (logical units) ──
constexpr int kWeatherSlot = 0;
constexpr int kCalendarSlot = 1;
constexpr int kClockSlot = 2;
constexpr int kRssSlot = 3;
constexpr int kCountdownSlot = 4;
constexpr int kPomodoroSlot = 5;
constexpr int kTimerSlot = 6;
constexpr int kSlotCount = 7;
constexpr float kWeatherW = 275.0f;
constexpr float kWeatherH = 145.0f;
constexpr float kMonthW = 145.0f;
constexpr float kMonthH = 145.0f;
constexpr float kUpcomingW = 275.0f;
constexpr float kUpcomingH = 145.0f;
constexpr float kAgendaW = 275.0f;
constexpr float kAgendaH = 290.0f;
constexpr float kTodayW = 145.0f;
constexpr float kTodayH = 145.0f;
constexpr float kClockSquare = 145.0f;
constexpr float kClockWideW = 275.0f;
constexpr float kClockWideH = 145.0f;
// Countdown and Pomodoro share one 145 x 145 square footprint.
constexpr float kFocusW = 145.0f;
constexpr float kFocusH = 145.0f;
// Radius of the Pomodoro's start and pause area, centred on the ring.
constexpr float kPomodoroCenterR = 46.0f;
// The timer is wide enough for its control and preset buttons in one row each.
constexpr float kTimerW = 275.0f;
constexpr float kTimerH = 145.0f;
// Match the Weather widget's default Medium footprint (275 x 145 logical pixels).
// Three 33 px headline rows plus the header and panel padding fit exactly.
constexpr float kRssW = kWeatherW;
constexpr float kRssHeaderH = 34.0f;
constexpr float kRssRowH = 33.0f;
constexpr float kRssMinH = 64.0f;
constexpr float kRssMaxH = kRssHeaderH + 20.0f * kRssRowH + 12.0f;
constexpr float kRssScrollW = 8.0f;
constexpr float kCornerRadius = 26.0f;
constexpr float kShadowPad = 10.0f;
constexpr float kSampleMargin = 24.0f;
constexpr float kPadX = 12.0f;
constexpr float kTitleY = 12.0f;  // header row shared by all widgets
constexpr float kWeekdayY = 28.0f;
constexpr float kGridY = 44.0f;
constexpr float kRowH = 15.0f;
constexpr float kCircleD = 14.0f;
constexpr float kUpcomingListW = 122.0f;
constexpr float kUpcomingGridX = 146.0f;
constexpr float kUpcomingGridW = 117.0f;
constexpr size_t kUpcomingRows = 3;
constexpr int kUpcomingWindowDays = 60;
constexpr int kAgendaDays = 7;
constexpr float kAgendaTop = 34.0f;
constexpr float kAgendaRowH = 34.0f;
constexpr float kPiF = 3.14159265f;

constexpr wchar_t kClassName[] = L"LvtWidgetsWindow";
constexpr UINT kSettingsChangedMessage = WM_APP + 1;
constexpr UINT kWeatherUpdatedMessage = WM_APP + 2;
constexpr UINT kCalendarUpdatedMessage = WM_APP + 3;
constexpr UINT kRssUpdatedMessage = WM_APP + 4;
constexpr UINT kTimerDoneMessage = WM_APP + 5;
constexpr UINT_PTR kWallpaperTimerId = 4;
constexpr UINT_PTR kAnimTimerId = 5;
constexpr UINT_PTR kDayTimerId = 6;
constexpr UINT_PTR kClockTimerId = 7;
constexpr UINT_PTR kFocusTimerId = 8;
constexpr UINT_PTR kTimerNotifyRemoveId = 9;
constexpr UINT kWallpaperPollMs = 3000;
constexpr UINT kDayTimerMs = 60000;
constexpr UINT kClockSlowMs = 15000;
constexpr wchar_t kDesktopKey[] = L"Control Panel\\Desktop";
constexpr wchar_t kColorsKey[] = L"Control Panel\\Colors";
constexpr wchar_t kZonesKey[] = L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Time Zones\\";

// Wallpaper placement modes (same values as DESKTOP_WALLPAPER_POSITION).
constexpr DWORD kPosCenter = 0;
constexpr DWORD kPosTile = 1;
constexpr DWORD kPosStretch = 2;
constexpr DWORD kPosFit = 3;
constexpr DWORD kPosFill = 4;
constexpr DWORD kPosSpan = 5;

// Calendar layouts.
enum CalLayout { kLayoutMonth = 0, kLayoutUpcoming = 1, kLayoutAgenda = 2, kLayoutToday = 3 };

// Clock layouts and styles.
enum ClockLayout {
    kClockAnalog = 0,
    kClockDigital = 1,
    kClockCityAnalog = 2,
    kClockCityDigital = 3,
    kClockWorldGrid = 4,
    kClockWorldList = 5,
};
enum ClockStyle { kStyleDark = 0, kStyleGlass = 1, kStyleLight = 2 };

const wchar_t* const kMonthNames[12] = {
    L"JANUARY", L"FEBRUARY", L"MARCH", L"APRIL", L"MAY", L"JUNE",
    L"JULY", L"AUGUST", L"SEPTEMBER", L"OCTOBER", L"NOVEMBER", L"DECEMBER",
};
const wchar_t* const kMonthAbbrev[12] = {
    L"Jan", L"Feb", L"Mar", L"Apr", L"May", L"Jun",
    L"Jul", L"Aug", L"Sep", L"Oct", L"Nov", L"Dec",
};
const wchar_t* const kDayAbbrev[7] = {L"Sun", L"Mon", L"Tue", L"Wed", L"Thu", L"Fri", L"Sat"};
const wchar_t* const kDayNames[7] = {
    L"SUNDAY", L"MONDAY", L"TUESDAY", L"WEDNESDAY", L"THURSDAY", L"FRIDAY", L"SATURDAY",
};

// ── Shared types ──

struct GlassSettings {
    int blurPx = 2;
    int refractionPx = 24;
    int bevelPx = 28;
    int chromaPct = 60;
    int specularPct = 120;
    int sheenPct = 20;
    int sheenWidthPct = 35;
    int rimPct = 90;
    int grainPct = 10;
    int shadowPct = 15;
    COLORREF tintTop = RGB(0x1A, 0x1F, 0x29);
    int tintTopOpacityPct = 15;
    COLORREF tintBottom = RGB(0x59, 0x66, 0x75);
    int tintBottomOpacityPct = 30;
    bool animate = false;
    int periodSec = 8;
    int fps = 30;
};

struct RenderSurface {
    HDC memDc = nullptr;
    HBITMAP bitmap = nullptr;
    HGDIOBJ oldBitmap = nullptr;
    void* bits = nullptr;
    int width = 0;
    int height = 0;
};

// ── Weather types ──

struct WeatherConfig {
    std::wstring label = L"Danville, CA 94526";
    double latitude = 37.8136;
    double longitude = -121.9978;
    bool celsius = false;
    int layout = 0; // 0=current/hourly, 1=one-day summary, 2=hourly + five-day
    bool useGpu = true;
    int refreshMinutes = 15;
    GlassSettings glass;
};

struct HourForecast {
    std::string time;
    double temp = 0.0;
    int code = 0;
    double precipitation = 0.0;
    double wind = 0.0;
};

struct DayForecast {
    std::string date;
    double high = 0.0;
    double low = 0.0;
    int code = 0;
    double precipitation = 0.0;
    double wind = 0.0;
};

struct WeatherData {
    bool valid = false;
    bool failed = false;
    std::string currentTime;
    double currentTemp = 0.0;
    int currentCode = 0;
    double dailyHigh = 0.0;
    double dailyLow = 0.0;
    double dailyPrecipitation = 0.0;
    double dailyWind = 0.0;
    std::vector<HourForecast> hours;
    std::vector<DayForecast> days;
};

enum class WeatherIcon { Clear, PartlyCloudy, Cloudy, Fog, Rain, Snow, Storm };

// Constant buffer for the glass shader. Layout must match GlassParams in kGlassHlsl.
struct GlassCB {
    float size[2];
    float crop[2];
    float margin;
    float radius;
    float edgeWidth;
    float refract;
    float blur;
    float chroma;
    float spec;
    float sheen;
    float rim;
    float grain;
    float scale;
    float shadow;
    float origin[2];
    float pad1[2];
    float tintTop[4];
    float tintBottom[4];
    float sheenWidth;
    float phase;
    float pad2[2];
};
static_assert(sizeof(GlassCB) == 128, "GlassCB must match the HLSL cbuffer layout");

// Render targets for one widget. Each widget has its own so sizes never fight.
struct GpuTargets {
    ID3D11Texture2D* rtTex = nullptr;
    ID3D11RenderTargetView* rtv = nullptr;
    ID3D11Texture2D* staging = nullptr;
    ID3D11Texture2D* cropTex = nullptr;
    ID3D11ShaderResourceView* cropSrv = nullptr;
    int outW = 0;
    int outH = 0;
    int cropW = 0;
    int cropH = 0;
};

struct GpuState {
    ID3D11Device* device = nullptr;
    ID3D11DeviceContext* ctx = nullptr;
    ID3D11VertexShader* vs = nullptr;
    ID3D11PixelShader* ps = nullptr;
    ID3D11Buffer* cb = nullptr;
    ID3D11SamplerState* sampler = nullptr;
    ID3D11RasterizerState* rasterState = nullptr;
    GpuTargets targets[kSlotCount];
    bool ready = false;
};

struct WallpaperPlacement {
    std::wstring path;
    DWORD position = kPosFill;
    COLORREF background = 0;
    RECT rect = {};
    std::wstring signature;
};

struct MonitorInfo {
    std::wstring id;
    RECT rc = {};
};

// Buffers for one widget: the wallpaper crop, the rendered widget, and the key of the crop.
struct SlotBuffers {
    std::vector<uint32_t> crop;
    std::vector<uint32_t> widget;
    std::wstring cropKey;
    // Cached GPU glass for this slot, reused while the crop and glass parameters are unchanged.
    std::vector<uint32_t> glass;
    GlassCB glassCb = {};
    bool glassValid = false;
    bool glassDark = false;
};

// ── Calendar types ──

struct CalendarConfig {
    std::wstring url;
    bool glass = true;
    bool showDots = true;
    int refreshMinutes = 60;
};

struct RssConfig {
    std::wstring url;
    int maxItems = 25;
    int visibleRows = 6;
    bool autoSize = false;
    int refreshMinutes = 15;
    COLORREF textColor = RGB(255, 255, 255);
    int textShadow = 70;
};

struct RssItem {
    std::wstring title;
    std::wstring link;
};

struct Ymd {
    int y = 1970;
    int m = 1;
    int d = 1;
};

enum class Freq { None, Daily, Weekly, Monthly, Yearly };

struct ByDay {
    int weekday = 0;
    int ordinal = 0;
};

struct Recurrence {
    Freq freq = Freq::None;
    int interval = 1;
    int count = 0;
    int64_t until = INT64_MAX;
    std::vector<ByDay> byDay;
    std::vector<int> byMonthDay;
    std::vector<int> byMonth;
};

struct TzRule {
    int offsetFrom = 0;
    int offsetTo = 0;
    int64_t startLocalMin = 0;
    Recurrence rule;
};

struct TzDef {
    std::vector<TzRule> rules;
};

struct TzTransition {
    int64_t utcMin;
    int offsetFrom;
    int offsetTo;
};

struct CalEvent {
    std::string uid;
    std::string summary;
    int64_t startDay = 0;
    int64_t durationDays = 1;
    Ymd startYmd;
    int startWeekday = 0;
    int startMinute = 0;
    bool allDay = false;
    bool utc = false;
    std::shared_ptr<const TzDef> tz;
    Recurrence rule;
    std::vector<int64_t> excluded;
};

struct LocalStart {
    int64_t day = 0;
    int minute = -1;
    bool allDay = false;
};

struct IcsWall {
    int64_t day = 0;
    int minute = 0;
    bool hasTime = false;
    bool utc = false;
};

struct RawEvent {
    std::string uid;
    std::string summary;
    std::string dtstart;
    std::string dtstartTzid;
    std::string dtend;
    std::string rrule;
    std::string recurrenceId;
    std::vector<std::string> exdates;
    bool cancelled = false;
};

enum class FetchStatus { NoUrl, Ok, Failed };

struct EventSnapshot {
    std::shared_ptr<const std::vector<CalEvent>> events;
    uint64_t version = 0;
    FetchStatus status = FetchStatus::NoUrl;
};

struct MonthMarks {
    int year = 0;
    int month = 0;
    uint64_t version = ~0ULL;
    std::vector<bool> days;
};

struct UpcomingItem {
    int64_t day = 0;
    int minute = 0;
    std::wstring title;
};

struct AgendaItem {
    int minute = 0;
    bool allDay = false;
    std::wstring title;
};

struct Ink {
    Color text;
    Color soft;
    Color dim;
    Color title;
    Color today;
    Color todayText;
    Color rowFill;
};

// ── Clock types ──

struct ClockConfig {
    int layout = kClockAnalog;
    int style = kStyleGlass;
    bool secondHand = true;
};

struct WorldCity {
    std::wstring code;
    std::wstring name;
    std::wstring zone;
    TIME_ZONE_INFORMATION tzi = {};
    bool valid = false;
};

// Local time and UTC offset for a time zone at the current moment.
struct ZoneNow {
    SYSTEMTIME local = {};
    int offsetMin = 0;
};

// One clock face: the time in that city and its offset from this PC's time zone.
struct ClockView {
    std::wstring code;
    std::wstring name;
    SYSTEMTIME t = {};
    int relMin = 0;
    int dayDelta = 0;
    bool valid = false;
};

struct ClockInk {
    Color face;
    Color ticks;
    Color hands;
    Color text;
    Color soft;
    Color accent;
};

// ── Global state ──
std::mutex g_mutex;  // guards the configs, weather data, events, cities, and calendar status
WeatherConfig g_weatherCfg;
WeatherData g_weather;
CalendarConfig g_calCfg;
RssConfig g_rssCfg;
ClockConfig g_clockCfg;
std::vector<WorldCity> g_cities;
std::shared_ptr<const std::vector<CalEvent>> g_events;
uint64_t g_eventsVersion = 0;
FetchStatus g_calStatus = FetchStatus::NoUrl;
std::shared_ptr<const std::vector<RssItem>> g_rssItems;
std::wstring g_rssFeedTitle;
FetchStatus g_rssStatus = FetchStatus::NoUrl;
std::atomic<int> g_rssScroll{0};
bool g_rssThumbDragging = false;
float g_rssThumbDragOffset = 0.0f;

// ── Countdown and Pomodoro ──

enum CountdownStatus { kCdNone = 0, kCdInvalid = 1, kCdOk = 2 };

struct CountdownConfig {
    std::wstring title = L"Countdown";
    std::wstring targetLabel;  // e.g. "Dec 25, 9:00 AM", shown under the numbers
    bool glass = true;
    int status = kCdNone;
    int64_t targetTicks = 0;   // UTC, in 100 ns FILETIME ticks
};

struct PomodoroConfig {
    bool glass = true;
    int workMin = 25;
    int breakMin = 5;
};

// Pomodoro timer state. Read and written only on the UI thread.
struct PomodoroState {
    bool initialized = false;
    bool work = true;
    bool running = false;
    int64_t remainingMs = 25 * 60 * 1000;
    ULONGLONG lastTickMs = 0;
    int completed = 0;
};

CountdownConfig g_countdownCfg;   // guarded by g_mutex
PomodoroConfig g_pomodoroCfg;     // guarded by g_mutex
PomodoroState g_pomo;             // UI thread only

// ── Timer ──

struct TimerConfig {
    bool glass = true;
    int customMin = 30;
};

// Timer state. Read and written only on the UI thread.
struct TimerState {
    bool initialized = false;
    int selected = 1;  // 0 = 5 min, 1 = 10 min, 2 = 15 min, 3 = custom
    int64_t durationMs = 10 * 60 * 1000;
    int64_t remainingMs = 10 * 60 * 1000;
    bool running = false;
    bool finished = false;
    ULONGLONG lastTickMs = 0;
};

TimerConfig g_timerCfg;  // guarded by g_mutex
TimerState g_timer;      // UI thread only

int64_t NowFileTimeTicks() {
    FILETIME ft = {};
    GetSystemTimeAsFileTime(&ft);
    ULARGE_INTEGER u;
    u.LowPart = ft.dwLowDateTime;
    u.HighPart = ft.dwHighDateTime;
    return static_cast<int64_t>(u.QuadPart);
}

// Parses "YYYY-MM-DD HH:MM" as local time (a T separator is also accepted). On success stores
// the UTC target in FILETIME ticks and a short display label.
int ParseCountdownTarget(std::wstring text, int64_t& ticks, std::wstring& label) {
    if (text.empty()) return kCdNone;
    for (wchar_t& c : text) {
        if (c == L'T') c = L' ';
    }
    int y = 0, mo = 0, d = 0, h = 0, mi = 0;
    if (swscanf_s(text.c_str(), L"%d-%d-%d %d:%d", &y, &mo, &d, &h, &mi) != 5) return kCdInvalid;
    if (y < 2000 || mo < 1 || mo > 12 || d < 1 || d > 31 || h < 0 || h > 23 || mi < 0 || mi > 59) {
        return kCdInvalid;
    }

    SYSTEMTIME local = {};
    local.wYear = static_cast<WORD>(y);
    local.wMonth = static_cast<WORD>(mo);
    local.wDay = static_cast<WORD>(d);
    local.wHour = static_cast<WORD>(h);
    local.wMinute = static_cast<WORD>(mi);

    SYSTEMTIME utc = {};
    FILETIME ft = {};
    if (!TzSpecificLocalTimeToSystemTime(nullptr, &local, &utc) || !SystemTimeToFileTime(&utc, &ft)) {
        return kCdInvalid;
    }
    ULARGE_INTEGER u;
    u.LowPart = ft.dwLowDateTime;
    u.HighPart = ft.dwHighDateTime;
    ticks = static_cast<int64_t>(u.QuadPart);

    const int h12 = h % 12 == 0 ? 12 : h % 12;
    wchar_t buf[64];
    swprintf_s(buf, L"%ls %d, %d:%02d %ls", kMonthAbbrev[mo - 1], d, h12, mi, h < 12 ? L"AM" : L"PM");
    label = buf;
    return kCdOk;
}

std::atomic<bool> g_slotEnabled[kSlotCount] = {};
std::atomic<int> g_calLayout{kLayoutMonth};
std::atomic<int> g_snapDistance{20};  // screen pixels; 0 disables edge snapping
std::atomic<int> g_snapGap{20};       // screen pixels kept between a snapped widget and an edge or widget
float g_slotSize[kSlotCount] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};

std::atomic<bool> g_stopping{false};
HWND g_hwnd = nullptr;
HANDLE g_uiThread = nullptr;
DWORD g_uiThreadId = 0;
HANDLE g_weatherThread = nullptr;
HANDLE g_calendarThread = nullptr;
HANDLE g_rssThread = nullptr;
HANDLE g_weatherWake = nullptr;
HANDLE g_calendarWake = nullptr;
HANDLE g_rssWake = nullptr;
ULONG_PTR g_gdiplusToken = 0;
float g_scale = 1.0f;

RectF g_slotRc[kSlotCount] = {RectF(0, 0, kWeatherW, kWeatherH), RectF(0, 0, kMonthW, kMonthH),
                              RectF(0, 0, kClockSquare, kClockSquare), RectF(0, 0, kRssW, kRssHeaderH + 6.0f * kRssRowH + 12.0f),
                              RectF(0, 0, kFocusW, kFocusH), RectF(0, 0, kFocusW, kFocusH),
                              RectF(0, 0, kTimerW, kTimerH)};
bool g_dragging = false;
bool g_dragMoved = false;
int g_dragSlot = -1;
PointF g_dragDelta;
PointF g_dragStart;
RenderSurface g_renderSurface;
// Presentation state. Each frame clears and presents the union of the widget areas drawn now and
// the ones drawn last frame, so a widget that moves or turns off leaves no pixels behind.
RECT g_prevPresentRect = {};
bool g_fullRefresh = true;

// GPU, wallpaper, calendar and clock state (UI thread only).
GpuState g_gpu;
SlotBuffers g_buffers[kSlotCount];
IDesktopWallpaper* g_desktopWallpaper = nullptr;
WallpaperPlacement g_wpPlacement;
Bitmap* g_wpImage = nullptr;
std::wstring g_wpImageKey;
MonthMarks g_marks;
int g_lastDayKey = 0;

// ── Geometry ──

float Clamp(float value, float minValue, float maxValue) {
    return std::max(minValue, std::min(value, maxValue));
}

RECT DesktopWorkArea() {
    RECT workArea = {};
    SystemParametersInfoW(SPI_GETWORKAREA, 0, &workArea, 0);
    return workArea;
}

float SlotScale(int slot) {
    return g_scale * g_slotSize[slot];
}

RectF& SlotRc(int slot) {
    return g_slotRc[slot];
}

bool SlotEnabled(int slot) {
    return g_slotEnabled[slot].load();
}

// Logical size of a widget before scaling.
WeatherConfig SnapshotWeather();
float WeatherWidgetHeight() {
    const WeatherConfig cfg = SnapshotWeather();
    return cfg.layout == 2 ? 260.0f : (cfg.layout == 1 ? 190.0f : kWeatherH);
}

RectF SlotBox(int slot) {
    if (slot == kRssSlot) {
        RssConfig cfg; int itemCount = 0;
        { std::lock_guard<std::mutex> lock(g_mutex); cfg = g_rssCfg; itemCount = g_rssItems ? static_cast<int>(g_rssItems->size()) : 0; }
        const int rows = cfg.autoSize ? std::min(std::max(1, itemCount), 20) : cfg.visibleRows;
        const float h = Clamp(kRssHeaderH + rows * kRssRowH + 12.0f, kRssMinH, kRssMaxH);
        return RectF(0, 0, kRssW, h);
    }
    if (slot == kCountdownSlot || slot == kPomodoroSlot) return RectF(0, 0, kFocusW, kFocusH);
    if (slot == kTimerSlot) return RectF(0, 0, kTimerW, kTimerH);
    if (slot == kWeatherSlot) return RectF(0, 0, kWeatherW, WeatherWidgetHeight());
    if (slot == kCalendarSlot) {
        switch (g_calLayout.load()) {
            case kLayoutUpcoming: return RectF(0, 0, kUpcomingW, kUpcomingH);
            case kLayoutAgenda: return RectF(0, 0, kAgendaW, kAgendaH);
            case kLayoutToday: return RectF(0, 0, kTodayW, kTodayH);
            default: return RectF(0, 0, kMonthW, kMonthH);
        }
    }
    const int layout = [] {
        std::lock_guard<std::mutex> lock(g_mutex);
        return g_clockCfg.layout;
    }();
    if (layout == kClockCityDigital || layout == kClockWorldList) {
        return RectF(0, 0, kClockWideW, kClockWideH);
    }
    return RectF(0, 0, kClockSquare, kClockSquare);
}

RECT SlotScreenRect(int slot) {
    const RECT wa = DesktopWorkArea();
    const float s = SlotScale(slot);
    const RectF& rc = SlotRc(slot);
    const RectF box = SlotBox(slot);
    const int x = wa.left + static_cast<int>(std::lround(rc.X * s));
    const int y = wa.top + static_cast<int>(std::lround(rc.Y * s));
    return RECT{x, y, x + static_cast<int>(std::lround(box.Width * s)),
                y + static_cast<int>(std::lround(box.Height * s))};
}

int HitTestSlot(POINT screenPt) {
    for (int slot = kSlotCount - 1; slot >= kWeatherSlot; --slot) {
        if (!SlotEnabled(slot)) continue;
        const RECT r = SlotScreenRect(slot);
        if (PtInRect(&r, screenPt)) return slot;
    }
    return -1;
}

PointF SlotLogicalPoint(int slot, LPARAM lParam) {
    const float s = SlotScale(slot);
    return PointF(GET_X_LPARAM(lParam) / s, GET_Y_LPARAM(lParam) / s);
}

void UpdateScale() {
    const float dpiScale = g_hwnd ? GetDpiForWindow(g_hwnd) / 96.0f : 1.0f;
    const float sw = GetSystemMetrics(SM_CXSCREEN) / dpiScale;
    const float sh = GetSystemMetrics(SM_CYSCREEN) / dpiScale;
    const float fit = (sw >= 1920.0f && sh >= 1080.0f)
        ? 1.0f
        : Clamp(std::min(sw / 1920.0f, sh / 1080.0f), 0.65f, 1.0f);
    g_scale = fit * dpiScale;
}

void ClampSlotToDesktop(int slot) {
    const RECT wa = DesktopWorkArea();
    const float s = SlotScale(slot);
    const RectF box = SlotBox(slot);
    const float maxX = std::max(0.0f, (wa.right - wa.left) / s - box.Width);
    const float maxY = std::max(0.0f, (wa.bottom - wa.top) / s - box.Height);
    RectF& rc = SlotRc(slot);
    rc.X = Clamp(rc.X, 0.0f, maxX);
    rc.Y = Clamp(rc.Y, 0.0f, maxY);
}

// Snaps a widget to the nearest matching edge within the snap distance. Targets are the
// screen edges and the edges of the other enabled widgets. Each axis snaps independently.
// Everything is computed in device pixels so widgets at different scales still line up.
void SnapSlotToEdges(int slot) {
    const int threshold = g_snapDistance.load();
    if (threshold <= 0) return;

    const RECT wa = DesktopWorkArea();
    const float areaW = static_cast<float>(wa.right - wa.left);
    const float areaH = static_cast<float>(wa.bottom - wa.top);
    const float s = SlotScale(slot);
    const RectF box = SlotBox(slot);
    const float w = box.Width * s;
    const float h = box.Height * s;
    const float tol = static_cast<float>(threshold);
    const float gap = static_cast<float>(g_snapGap.load());

    RectF& rc = SlotRc(slot);
    const float x = rc.X * s;
    const float y = rc.Y * s;

    float bestX = x, bestXDist = tol + 1.0f;
    float bestY = y, bestYDist = tol + 1.0f;
    auto considerX = [&](float cand) {
        const float d = std::fabs(cand - x);
        if (d <= tol && d < bestXDist) { bestXDist = d; bestX = cand; }
    };
    auto considerY = [&](float cand) {
        const float d = std::fabs(cand - y);
        if (d <= tol && d < bestYDist) { bestYDist = d; bestY = cand; }
    };

    // Screen edges, inset by the gap.
    considerX(gap);
    considerX(areaW - w - gap);
    considerY(gap);
    considerY(areaH - h - gap);

    // Other widgets: align edges with the same side, and touch the opposite side.
    for (int other = 0; other < kSlotCount; ++other) {
        if (other == slot || !SlotEnabled(other)) continue;
        const float os = SlotScale(other);
        const RectF ob = SlotBox(other);
        const float ox = SlotRc(other).X * os;
        const float oy = SlotRc(other).Y * os;
        const float ow = ob.Width * os;
        const float oh = ob.Height * os;

        considerX(ox);
        considerX(ox + ow - w);
        considerX(ox + ow + gap);
        considerX(ox - w - gap);
        considerY(oy);
        considerY(oy + oh - h);
        considerY(oy + oh + gap);
        considerY(oy - h - gap);
    }

    // Keep the snapped position on the screen.
    bestX = Clamp(bestX, 0.0f, std::max(0.0f, areaW - w));
    bestY = Clamp(bestY, 0.0f, std::max(0.0f, areaH - h));
    rc.X = bestX / s;
    rc.Y = bestY / s;
}

void ApplyDefaultPosition(int slot) {
    const RECT wa = DesktopWorkArea();
    const float s = SlotScale(slot);
    const float screenW = (wa.right - wa.left) / s;
    RectF& rc = SlotRc(slot);
    rc.X = std::max(0.0f, screenW - kWeatherW - 40.0f);
    rc.Y = slot == kWeatherSlot ? 60.0f : (slot == kCalendarSlot ? 260.0f : (slot == kClockSlot ? 460.0f : 660.0f));
    if (slot == kRssSlot) rc.X = 40.0f;
    if (slot == kCountdownSlot) rc.Y = 620.0f;
    if (slot == kPomodoroSlot) rc.Y = 780.0f;
    if (slot == kTimerSlot) {
        rc.X = 40.0f;
        rc.Y = 60.0f;
    }
}

const wchar_t* SlotPositionKey(int slot) {
    if (slot == kWeatherSlot) return L"weatherPosition";
    if (slot == kCalendarSlot) return L"calendarPosition";
    if (slot == kClockSlot) return L"clockPosition";
    if (slot == kCountdownSlot) return L"countdownPosition";
    if (slot == kPomodoroSlot) return L"pomodoroPosition";
    if (slot == kTimerSlot) return L"timerPosition";
    return L"rssPosition";
}

void SaveSlotPosition(int slot) {
    const RectF& rc = SlotRc(slot);
    wchar_t value[64];
    swprintf_s(value, L"%.2f,%.2f", rc.X, rc.Y);
    Wh_SetStringValue(SlotPositionKey(slot), value);
}

bool LoadSlotPosition(int slot) {
    wchar_t value[64];
    if (Wh_GetStringValue(SlotPositionKey(slot), value, ARRAYSIZE(value)) == 0) return false;
    float x = 0.0f, y = 0.0f;
    if (swscanf_s(value, L"%f,%f", &x, &y) != 2) return false;
    RectF& rc = SlotRc(slot);
    rc.X = x;
    rc.Y = y;
    return true;
}

// ── Date helpers ──

int64_t FloorDiv(int64_t a, int64_t b) {
    return a >= 0 ? a / b : -((-a + b - 1) / b);
}

int64_t DaysFromCivil(int y, int m, int d) {
    y -= m <= 2 ? 1 : 0;
    const int64_t era = (y >= 0 ? y : y - 399) / 400;
    const int64_t yoe = y - era * 400;
    const int64_t mp = m > 2 ? m - 3 : m + 9;
    const int64_t doy = (153 * mp + 2) / 5 + d - 1;
    const int64_t doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
    return era * 146097 + doe - 719468;
}

Ymd CivilFromDays(int64_t z) {
    z += 719468;
    const int64_t era = (z >= 0 ? z : z - 146096) / 146097;
    const int64_t doe = z - era * 146097;
    const int64_t yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;
    const int64_t y = yoe + era * 400;
    const int64_t doy = doe - (365 * yoe + yoe / 4 - yoe / 100);
    const int64_t mp = (5 * doy + 2) / 153;
    const int64_t d = doy - (153 * mp + 2) / 5 + 1;
    const int64_t m = mp < 10 ? mp + 3 : mp - 9;
    Ymd out;
    out.y = static_cast<int>(y + (m <= 2 ? 1 : 0));
    out.m = static_cast<int>(m);
    out.d = static_cast<int>(d);
    return out;
}

// 0 = Sunday ... 6 = Saturday. 1970-01-01 was a Thursday.
int Weekday(int64_t day) {
    return static_cast<int>(((day + 4) % 7 + 7) % 7);
}

int DaysInMonth(int y, int m) {
    const int64_t first = DaysFromCivil(y, m, 1);
    const int ny = m == 12 ? y + 1 : y;
    const int nm = m == 12 ? 1 : m + 1;
    return static_cast<int>(DaysFromCivil(ny, nm, 1) - first);
}

int MinuteOfDay(int64_t minute) {
    return static_cast<int>(((minute % 1440) + 1440) % 1440);
}

// Minutes since 1970 for a SYSTEMTIME.
int64_t AbsMinutes(const SYSTEMTIME& st) {
    return DaysFromCivil(st.wYear, st.wMonth, st.wDay) * 1440 + st.wHour * 60 + st.wMinute;
}

// ── Settings ──

std::wstring TrimSetting(const std::wstring& text) {
    const wchar_t* junk = L" \t\r\n\"'";
    const size_t first = text.find_first_not_of(junk);
    if (first == std::wstring::npos) return L"";
    const size_t last = text.find_last_not_of(junk);
    return text.substr(first, last - first + 1);
}

bool ReadBoolSetting(const wchar_t* name, bool defaultValue) {
    if (Wh_GetIntSetting(name) != 0) return true;
    PCWSTR value = Wh_GetStringSetting(name);
    if (!value) return defaultValue;
    bool result = false;
    if (wcscmp(value, L"true") == 0 || wcscmp(value, L"1") == 0 || wcscmp(value, L"on") == 0) {
        result = true;
    }
    Wh_FreeStringSetting(value);
    return result;
}

float SizeFactorSetting(const wchar_t* name) {
    float factor = 1.0f;
    if (PCWSTR size = Wh_GetStringSetting(name)) {
        if (wcscmp(size, L"small") == 0) factor = 0.8f;
        else if (wcscmp(size, L"large") == 0) factor = 1.25f;
        Wh_FreeStringSetting(size);
    }
    return factor;
}

bool ParseHexColor(const std::wstring& text, COLORREF& out) {
    std::wstring t = text;
    if (!t.empty() && t[0] == L'#') t.erase(0, 1);
    if (t.size() != 6) return false;
    unsigned v = 0;
    for (wchar_t c : t) {
        v <<= 4;
        if (c >= L'0' && c <= L'9') v += static_cast<unsigned>(c - L'0');
        else if (c >= L'a' && c <= L'f') v += static_cast<unsigned>(c - L'a' + 10);
        else if (c >= L'A' && c <= L'F') v += static_cast<unsigned>(c - L'A' + 10);
        else return false;
    }
    out = RGB((v >> 16) & 0xFF, (v >> 8) & 0xFF, v & 0xFF);
    return true;
}

GlassSettings LoadGlassSettings() {
    GlassSettings gs;
    gs.blurPx = std::clamp(Wh_GetIntSetting(L"glassBlur"), 0, 20);
    gs.refractionPx = std::clamp(Wh_GetIntSetting(L"glassRefraction"), 0, 30);
    gs.bevelPx = std::clamp(Wh_GetIntSetting(L"glassBevel"), 4, 40);
    gs.chromaPct = std::clamp(Wh_GetIntSetting(L"glassChromatic"), 0, 100);
    gs.specularPct = std::clamp(Wh_GetIntSetting(L"glassSpecular"), 0, 200);
    gs.sheenPct = std::clamp(Wh_GetIntSetting(L"glassSheen"), 0, 100);
    gs.sheenWidthPct = std::clamp(Wh_GetIntSetting(L"glassSheenWidth"), 10, 100);
    gs.rimPct = std::clamp(Wh_GetIntSetting(L"glassRim"), 0, 150);
    gs.grainPct = std::clamp(Wh_GetIntSetting(L"glassGrain"), 0, 100);
    gs.shadowPct = std::clamp(Wh_GetIntSetting(L"glassShadow"), 0, 100);
    gs.tintTopOpacityPct = std::clamp(Wh_GetIntSetting(L"glassTintTopOpacity"), 0, 100);
    gs.tintBottomOpacityPct = std::clamp(Wh_GetIntSetting(L"glassTintBottomOpacity"), 0, 100);

    if (PCWSTR c = Wh_GetStringSetting(L"glassTintTop")) {
        COLORREF rgb = 0;
        if (ParseHexColor(c, rgb)) gs.tintTop = rgb;
        Wh_FreeStringSetting(c);
    }
    if (PCWSTR c = Wh_GetStringSetting(L"glassTintBottom")) {
        COLORREF rgb = 0;
        if (ParseHexColor(c, rgb)) gs.tintBottom = rgb;
        Wh_FreeStringSetting(c);
    }

    gs.animate = ReadBoolSetting(L"sheenAnimation", false);
    gs.periodSec = std::clamp(Wh_GetIntSetting(L"sheenPeriod"), 2, 60);
    gs.fps = std::clamp(Wh_GetIntSetting(L"animationFps"), 10, 60);
    return gs;
}

// ── Clock: time zones from the Windows registry ──

// Reads a Windows time zone definition (the TZI value) into a TIME_ZONE_INFORMATION.
bool LoadZoneInfo(const std::wstring& zoneId, TIME_ZONE_INFORMATION& tzi) {
    const std::wstring key = std::wstring(kZonesKey) + zoneId;
    HKEY hk = nullptr;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, key.c_str(), 0, KEY_READ, &hk) != ERROR_SUCCESS) return false;

    struct RegTzi {
        LONG bias;
        LONG stdBias;
        LONG dstBias;
        SYSTEMTIME stdDate;
        SYSTEMTIME dstDate;
    } raw = {};
    DWORD size = sizeof(raw);
    DWORD type = 0;
    const LONG r = RegQueryValueExW(hk, L"TZI", nullptr, &type, reinterpret_cast<LPBYTE>(&raw), &size);
    RegCloseKey(hk);
    if (r != ERROR_SUCCESS || type != REG_BINARY || size < sizeof(raw)) return false;

    ZeroMemory(&tzi, sizeof(tzi));
    tzi.Bias = raw.bias;
    tzi.StandardBias = raw.stdBias;
    tzi.DaylightBias = raw.dstBias;
    tzi.StandardDate = raw.stdDate;
    tzi.DaylightDate = raw.dstDate;
    return true;
}

// Current local time and UTC offset. A null zone means this PC's time zone.
ZoneNow GetZoneNow(const TIME_ZONE_INFORMATION* tzi) {
    SYSTEMTIME utc = {};
    GetSystemTime(&utc);
    ZoneNow z;
    if (!SystemTimeToTzSpecificLocalTime(tzi, &utc, &z.local)) {
        GetLocalTime(&z.local);
    }
    z.offsetMin = static_cast<int>(AbsMinutes(z.local) - AbsMinutes(utc));
    return z;
}

std::vector<std::wstring> SplitW(const std::wstring& text, wchar_t sep) {
    std::vector<std::wstring> out;
    size_t start = 0;
    while (true) {
        const size_t p = text.find(sep, start);
        out.push_back(text.substr(start, p == std::wstring::npos ? std::wstring::npos : p - start));
        if (p == std::wstring::npos) break;
        start = p + 1;
    }
    return out;
}

// Parses "code|City|Windows zone;..." into at most four cities.
std::vector<WorldCity> ParseCities(const std::wstring& text) {
    std::vector<WorldCity> cities;
    for (const std::wstring& entry : SplitW(text, L';')) {
        const std::vector<std::wstring> parts = SplitW(entry, L'|');
        if (parts.size() < 3) continue;
        WorldCity c;
        c.code = TrimSetting(parts[0]);
        c.name = TrimSetting(parts[1]);
        c.zone = TrimSetting(parts[2]);
        if (c.code.empty() || c.zone.empty()) continue;
        c.valid = LoadZoneInfo(c.zone, c.tzi);
        cities.push_back(c);
        if (cities.size() >= 4) break;
    }
    return cities;
}

// ── Settings loading ──

void LoadSettings() {
    WeatherConfig w;
    w.useGpu = true;
    if (PCWSTR label = Wh_GetStringSetting(L"locationLabel")) {
        if (label[0]) w.label = label;
        Wh_FreeStringSetting(label);
    }
    if (PCWSTR lat = Wh_GetStringSetting(L"latitude")) {
        const double v = _wtof(lat);
        if (lat[0] && v >= -90.0 && v <= 90.0) w.latitude = v;
        Wh_FreeStringSetting(lat);
    }
    if (PCWSTR lon = Wh_GetStringSetting(L"longitude")) {
        const double v = _wtof(lon);
        if (lon[0] && v >= -180.0 && v <= 180.0) w.longitude = v;
        Wh_FreeStringSetting(lon);
    }
    if (PCWSTR units = Wh_GetStringSetting(L"temperatureUnits")) {
        w.celsius = wcscmp(units, L"celsius") == 0;
        Wh_FreeStringSetting(units);
    }
    if (PCWSTR glass = Wh_GetStringSetting(L"glassRendering")) {
        w.useGpu = wcscmp(glass, L"cpu") != 0;
        Wh_FreeStringSetting(glass);
    }
    if (PCWSTR layout = Wh_GetStringSetting(L"weatherLayout")) {
        if (wcscmp(layout, L"day") == 0) w.layout = 1;
        else if (wcscmp(layout, L"extended") == 0) w.layout = 2;
        Wh_FreeStringSetting(layout);
    }
    const int weatherMinutes = Wh_GetIntSetting(L"weatherRefreshMinutes");
    w.refreshMinutes = weatherMinutes >= 5 ? std::min(weatherMinutes, 240) : 15;
    w.glass = LoadGlassSettings();

    CalendarConfig c;
    if (PCWSTR url = Wh_GetStringSetting(L"calendarUrl")) {
        c.url = TrimSetting(url);
        Wh_FreeStringSetting(url);
    }
    if (PCWSTR style = Wh_GetStringSetting(L"calendarStyle")) {
        c.glass = wcscmp(style, L"dark") != 0;
        Wh_FreeStringSetting(style);
    }
    c.showDots = ReadBoolSetting(L"showEventDots", true);
    const int calMinutes = Wh_GetIntSetting(L"calendarRefreshMinutes");
    c.refreshMinutes = calMinutes >= 5 ? std::min(calMinutes, 1440) : 60;

    int calLayout = kLayoutMonth;
    if (PCWSTR value = Wh_GetStringSetting(L"calendarLayout")) {
        if (wcscmp(value, L"upcoming") == 0) calLayout = kLayoutUpcoming;
        else if (wcscmp(value, L"agenda") == 0) calLayout = kLayoutAgenda;
        else if (wcscmp(value, L"today") == 0) calLayout = kLayoutToday;
        Wh_FreeStringSetting(value);
    }

    RssConfig rss;
    if (PCWSTR url = Wh_GetStringSetting(L"rssUrl")) { rss.url = TrimSetting(url); Wh_FreeStringSetting(url); }
    if (rss.url.empty()) rss.url = L"https://www.pbs.org/newshour/feeds/rss/headlines";
    rss.maxItems = std::clamp(Wh_GetIntSetting(L"rssMaxItems"), 1, 200);
    if (rss.maxItems == 0) rss.maxItems = 25;
    rss.visibleRows = std::clamp(Wh_GetIntSetting(L"rssVisibleRows"), 1, 20);
    if (rss.visibleRows == 0) rss.visibleRows = 6;
    rss.autoSize = ReadBoolSetting(L"rssAutoSize", false);
    const int rssMinutes = Wh_GetIntSetting(L"rssRefreshMinutes");
    rss.refreshMinutes = rssMinutes >= 5 ? std::min(rssMinutes, 240) : 15;
    if (PCWSTR color = Wh_GetStringSetting(L"rssTextColor")) {
        ParseHexColor(color, rss.textColor);
        Wh_FreeStringSetting(color);
    }
    rss.textShadow = std::clamp(Wh_GetIntSetting(L"rssTextShadow"), 0, 100);

    ClockConfig cc;
    if (PCWSTR value = Wh_GetStringSetting(L"clockLayout")) {
        if (wcscmp(value, L"digital") == 0) cc.layout = kClockDigital;
        else if (wcscmp(value, L"cityAnalog") == 0) cc.layout = kClockCityAnalog;
        else if (wcscmp(value, L"cityDigital") == 0) cc.layout = kClockCityDigital;
        else if (wcscmp(value, L"worldGrid") == 0) cc.layout = kClockWorldGrid;
        else if (wcscmp(value, L"worldList") == 0) cc.layout = kClockWorldList;
        Wh_FreeStringSetting(value);
    }
    if (PCWSTR value = Wh_GetStringSetting(L"clockStyle")) {
        if (wcscmp(value, L"dark") == 0) cc.style = kStyleDark;
        else if (wcscmp(value, L"light") == 0) cc.style = kStyleLight;
        Wh_FreeStringSetting(value);
    }
    cc.secondHand = ReadBoolSetting(L"clockSecondHand", true);

    std::vector<WorldCity> cities;
    if (PCWSTR value = Wh_GetStringSetting(L"clockWorlds")) {
        cities = ParseCities(value);
        Wh_FreeStringSetting(value);
    }

    const bool weatherOn = ReadBoolSetting(L"showWeather", true);
    const bool calendarOn = ReadBoolSetting(L"showCalendar", true);
    const bool clockOn = ReadBoolSetting(L"showClock", true);
    const bool rssOn = ReadBoolSetting(L"showRss", true);

    CountdownConfig cdc;
    if (PCWSTR value = Wh_GetStringSetting(L"countdownTitle")) {
        const std::wstring title = TrimSetting(value);
        if (!title.empty()) cdc.title = title;
        Wh_FreeStringSetting(value);
    }
    if (PCWSTR value = Wh_GetStringSetting(L"countdownDate")) {
        cdc.status = ParseCountdownTarget(TrimSetting(value), cdc.targetTicks, cdc.targetLabel);
        Wh_FreeStringSetting(value);
    }
    if (PCWSTR value = Wh_GetStringSetting(L"countdownStyle")) {
        cdc.glass = wcscmp(value, L"dark") != 0;
        Wh_FreeStringSetting(value);
    }
    PomodoroConfig pmc;
    pmc.workMin = std::clamp(Wh_GetIntSetting(L"pomodoroWorkMinutes"), 1, 120);
    pmc.breakMin = std::clamp(Wh_GetIntSetting(L"pomodoroBreakMinutes"), 1, 60);
    if (PCWSTR value = Wh_GetStringSetting(L"pomodoroStyle")) {
        pmc.glass = wcscmp(value, L"dark") != 0;
        Wh_FreeStringSetting(value);
    }
    const bool countdownOn = ReadBoolSetting(L"showCountdown", true);
    const bool pomodoroOn = ReadBoolSetting(L"showPomodoro", true);

    TimerConfig tmc;
    tmc.customMin = std::clamp(Wh_GetIntSetting(L"timerCustomMinutes"), 1, 720);
    if (PCWSTR value = Wh_GetStringSetting(L"timerStyle")) {
        tmc.glass = wcscmp(value, L"dark") != 0;
        Wh_FreeStringSetting(value);
    }
    const bool timerOn = ReadBoolSetting(L"showTimer", true);

    {
        std::lock_guard<std::mutex> lock(g_mutex);
        g_weatherCfg = w;
        g_calCfg = c;
        g_rssCfg = rss;
        g_countdownCfg = cdc;
        g_pomodoroCfg = pmc;
        g_timerCfg = tmc;
        g_clockCfg = cc;
        g_cities = cities;
        g_calStatus = c.url.empty() ? FetchStatus::NoUrl : g_calStatus;
    }
    g_slotEnabled[kWeatherSlot] = weatherOn;
    g_slotEnabled[kCalendarSlot] = calendarOn;
    g_slotEnabled[kClockSlot] = clockOn;
    g_slotEnabled[kRssSlot] = rssOn;
    g_slotEnabled[kCountdownSlot] = countdownOn;
    g_slotEnabled[kPomodoroSlot] = pomodoroOn;
    g_slotEnabled[kTimerSlot] = timerOn;
    g_calLayout = calLayout;
    g_snapDistance = std::clamp(Wh_GetIntSetting(L"snapDistance"), 0, 200);
    g_snapGap = std::clamp(Wh_GetIntSetting(L"snapGap"), 0, 200);
    g_slotSize[kWeatherSlot] = SizeFactorSetting(L"weatherSize");
    g_slotSize[kCalendarSlot] = SizeFactorSetting(L"calendarSize");
    g_slotSize[kClockSlot] = SizeFactorSetting(L"clockSize");
    g_slotSize[kRssSlot] = 1.0f;
    g_slotSize[kCountdownSlot] = 1.0f;
    g_slotSize[kPomodoroSlot] = 1.0f;
    g_slotSize[kTimerSlot] = 1.0f;
}

WeatherConfig SnapshotWeather() {
    std::lock_guard<std::mutex> lock(g_mutex);
    return g_weatherCfg;
}

CalendarConfig SnapshotCalendar() {
    std::lock_guard<std::mutex> lock(g_mutex);
    return g_calCfg;
}

RssConfig SnapshotRss() { std::lock_guard<std::mutex> lock(g_mutex); return g_rssCfg; }

ClockConfig SnapshotClock() {
    std::lock_guard<std::mutex> lock(g_mutex);
    return g_clockCfg;
}

std::vector<WorldCity> SnapshotCities() {
    std::lock_guard<std::mutex> lock(g_mutex);
    return g_cities;
}

EventSnapshot SnapshotEvents() {
    std::lock_guard<std::mutex> lock(g_mutex);
    EventSnapshot snap;
    snap.events = g_events;
    snap.version = g_eventsVersion;
    snap.status = g_calStatus;
    return snap;
}

// ── JSON helpers (Open-Meteo responses are small and well-formed) ──

const char* SkipWs(const char* p) {
    while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n') ++p;
    return p;
}

const char* FindValue(const char* begin, const char* end, const char* key) {
    const size_t keyLen = std::strlen(key);
    for (const char* p = begin; p + keyLen + 2 < end; ++p) {
        if (*p == '"' && p[keyLen + 1] == '"' && std::strncmp(p + 1, key, keyLen) == 0) {
            const char* q = SkipWs(p + keyLen + 2);
            if (*q == ':') return SkipWs(q + 1);
        }
    }
    return nullptr;
}

const char* ObjectEnd(const char* p, const char* end) {
    int depth = 0;
    for (; p < end; ++p) {
        if (*p == '{') {
            ++depth;
        } else if (*p == '}' && --depth == 0) {
            return p + 1;
        }
    }
    return end;
}

bool ReadNumber(const char* p, double& out) {
    p = SkipWs(p);
    char* stop = nullptr;
    const double v = std::strtod(p, &stop);
    if (stop == p) return false;
    out = v;
    return true;
}

bool ReadString(const char* p, std::string& out) {
    p = SkipWs(p);
    if (*p != '"') return false;
    const char* close = std::strchr(p + 1, '"');
    if (!close) return false;
    out.assign(p + 1, close);
    return true;
}

bool ReadNumberArray(const char* p, std::vector<double>& out) {
    out.clear();
    p = SkipWs(p);
    if (*p != '[') return false;
    ++p;
    while (*p && *p != ']') {
        p = SkipWs(p);
        if (*p == ',') { ++p; continue; }
        if (*p == ']') break;
        char* stop = nullptr;
        const double v = std::strtod(p, &stop);
        if (stop == p) {
            out.push_back(std::nan(""));
            while (*p && *p != ',' && *p != ']') ++p;
        } else {
            out.push_back(v);
            p = stop;
        }
    }
    return *p == ']';
}

bool ReadStringArray(const char* p, std::vector<std::string>& out) {
    out.clear();
    p = SkipWs(p);
    if (*p != '[') return false;
    for (++p; *p && *p != ']'; ++p) {
        if (*p == '"') {
            const char* close = std::strchr(p + 1, '"');
            if (!close) return false;
            out.emplace_back(p + 1, close);
            p = close;
        }
    }
    return *p == ']';
}

bool ParseForecast(const std::string& body, WeatherData& out) {
    const char* begin = body.c_str();
    const char* end = begin + body.size();

    const char* cur = FindValue(begin, end, "current");
    if (!cur || *cur != '{') return false;
    const char* curEnd = ObjectEnd(cur, end);
    const char* p = FindValue(cur, curEnd, "time");
    if (!p || !ReadString(p, out.currentTime)) return false;
    p = FindValue(cur, curEnd, "temperature_2m");
    if (!p || !ReadNumber(p, out.currentTemp)) return false;
    double code = 0.0;
    p = FindValue(cur, curEnd, "weather_code");
    if (!p || !ReadNumber(p, code)) return false;
    out.currentCode = static_cast<int>(code);

    const char* hourly = FindValue(begin, end, "hourly");
    if (!hourly || *hourly != '{') return false;
    const char* hourlyEnd = ObjectEnd(hourly, end);
    std::vector<std::string> times;
    std::vector<double> temps;
    std::vector<double> codes, precip, wind;

    p = FindValue(hourly, hourlyEnd, "time");
    if (!p || !ReadStringArray(p, times)) return false;
    p = FindValue(hourly, hourlyEnd, "temperature_2m");
    if (!p || !ReadNumberArray(p, temps)) return false;
    p = FindValue(hourly, hourlyEnd, "weather_code");
    if (!p || !ReadNumberArray(p, codes)) return false;
    p = FindValue(hourly, hourlyEnd, "precipitation_probability");
    if (p) ReadNumberArray(p, precip);
    p = FindValue(hourly, hourlyEnd, "wind_speed_10m");
    if (p) ReadNumberArray(p, wind);

    const std::string nowHour = out.currentTime.substr(0, 13);
    size_t start = 0;
    while (start < times.size() && times[start].compare(0, 13, nowHour) < 0) ++start;
    out.hours.clear();
    for (size_t i = start;
         i < times.size() && i < start + 6 && i < temps.size() && i < codes.size(); ++i) {
        out.hours.push_back({times[i], temps[i], static_cast<int>(codes[i]),
            i < precip.size() ? precip[i] : 0.0, i < wind.size() ? wind[i] : 0.0});
    }

    const char* daily = FindValue(begin, end, "daily");
    if (!daily || *daily != '{') return false;
    const char* dailyEnd = ObjectEnd(daily, end);
    std::vector<double> highs, lows, dailyCodes, dailyPrecip, dailyWind;
    std::vector<std::string> dates;

    p = FindValue(daily, dailyEnd, "temperature_2m_max");
    if (!p || !ReadNumberArray(p, highs) || highs.empty()) return false;
    p = FindValue(daily, dailyEnd, "temperature_2m_min");
    if (!p || !ReadNumberArray(p, lows) || lows.empty()) return false;

    out.dailyHigh = highs[0];
    out.dailyLow = lows[0];
    p = FindValue(daily, dailyEnd, "time"); if (p) ReadStringArray(p, dates);
    p = FindValue(daily, dailyEnd, "weather_code"); if (p) ReadNumberArray(p, dailyCodes);
    p = FindValue(daily, dailyEnd, "precipitation_sum"); if (p) ReadNumberArray(p, dailyPrecip);
    p = FindValue(daily, dailyEnd, "wind_speed_10m_max"); if (p) ReadNumberArray(p, dailyWind);
    out.dailyPrecipitation = dailyPrecip.empty() ? 0.0 : dailyPrecip[0];
    out.dailyWind = dailyWind.empty() ? 0.0 : dailyWind[0];
    out.days.clear();
    for (size_t i = 0; i < dates.size() && i < 5 && i < highs.size() && i < lows.size(); ++i)
        out.days.push_back({dates[i], highs[i], lows[i],
            i < dailyCodes.size() ? static_cast<int>(dailyCodes[i]) : 0,
            i < dailyPrecip.size() ? dailyPrecip[i] : 0.0,
            i < dailyWind.size() ? dailyWind[i] : 0.0});
    out.valid = true;
    out.failed = false;
    return true;
}

bool FetchForecast(const WeatherConfig& cfg, WeatherData& out) {
    wchar_t url[768];
    swprintf_s(url, ARRAYSIZE(url),
        L"https://api.open-meteo.com/v1/forecast"
        L"?latitude=%.4f&longitude=%.4f"
        L"&current=temperature_2m,weather_code"
        L"&hourly=temperature_2m,weather_code,precipitation_probability,wind_speed_10m"
        L"&daily=temperature_2m_max,temperature_2m_min,weather_code,precipitation_sum,wind_speed_10m_max"
        L"&temperature_unit=%ls&wind_speed_unit=kmh&precipitation_unit=mm&timezone=auto&forecast_days=5",
        cfg.latitude, cfg.longitude, cfg.celsius ? L"celsius" : L"fahrenheit");

    const WH_URL_CONTENT* content = Wh_GetUrlContent(url, nullptr);
    if (!content) return false;

    bool ok = false;
    if (content->statusCode == 200 && content->data && content->length > 0) {
        const std::string body(content->data, content->length);
        ok = ParseForecast(body, out);
    }
    Wh_FreeUrlContent(content);
    return ok;
}

// ── Calendar: iCalendar text helpers ──

std::vector<std::string> SplitList(const std::string& text, char sep) {
    std::vector<std::string> out;
    size_t start = 0;
    while (true) {
        const size_t p = text.find(sep, start);
        out.push_back(text.substr(start, p == std::string::npos ? std::string::npos : p - start));
        if (p == std::string::npos) break;
        start = p + 1;
    }
    return out;
}

std::vector<std::string> UnfoldIcsLines(const std::string& text) {
    std::vector<std::string> lines;
    size_t pos = 0;
    while (pos < text.size()) {
        size_t end = text.find('\n', pos);
        if (end == std::string::npos) end = text.size();
        std::string line = text.substr(pos, end - pos);
        if (!line.empty() && line.back() == '\r') line.pop_back();
        pos = end + 1;
        if (!line.empty() && (line[0] == ' ' || line[0] == '\t') && !lines.empty()) {
            lines.back() += line.substr(1);
        } else {
            lines.push_back(line);
        }
    }
    return lines;
}

struct IcsProp {
    std::string name;
    std::string params;
    std::string value;
};

bool SplitIcsProp(const std::string& line, IcsProp& out) {
    const size_t colon = line.find(':');
    if (colon == std::string::npos) return false;
    const std::string left = line.substr(0, colon);
    out.value = line.substr(colon + 1);
    const size_t semi = left.find(';');
    out.name = left.substr(0, semi);
    out.params = semi == std::string::npos ? std::string() : left.substr(semi + 1);
    return true;
}

std::string GetParam(const std::string& params, const std::string& name) {
    for (const std::string& part : SplitList(params, ';')) {
        const size_t eq = part.find('=');
        if (eq == std::string::npos) continue;
        if (part.substr(0, eq) != name) continue;
        std::string value = part.substr(eq + 1);
        if (value.size() >= 2 && value.front() == '"' && value.back() == '"') {
            value = value.substr(1, value.size() - 2);
        }
        return value;
    }
    return "";
}

std::string UnescapeIcsText(const std::string& s) {
    std::string out;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '\\' && i + 1 < s.size()) {
            const char next = s[i + 1];
            if (next == 'n' || next == 'N') out += ' ';
            else out += next;
            ++i;
        } else {
            out += s[i];
        }
    }
    return out;
}

std::wstring Utf8ToWide(const std::string& s) {
    if (s.empty()) return L"";
    const int n = MultiByteToWideChar(CP_UTF8, 0, s.data(), static_cast<int>(s.size()), nullptr, 0);
    if (n <= 0) return L"";
    std::wstring out(static_cast<size_t>(n), L'\0');
    MultiByteToWideChar(CP_UTF8, 0, s.data(), static_cast<int>(s.size()), &out[0], n);
    return out;
}

int ReadInt(const std::string& s, size_t pos, size_t len) {
    if (pos + len > s.size()) return -1;
    return std::atoi(s.substr(pos, len).c_str());
}

bool ParseIcsWall(const std::string& v, IcsWall& out) {
    const int y = ReadInt(v, 0, 4);
    const int m = ReadInt(v, 4, 2);
    const int d = ReadInt(v, 6, 2);
    if (y < 0 || m < 1 || m > 12 || d < 1 || d > 31) return false;

    out = IcsWall();
    out.day = DaysFromCivil(y, m, d);
    if (v.size() >= 15 && v[8] == 'T') {
        const int hh = ReadInt(v, 9, 2);
        const int mm = ReadInt(v, 11, 2);
        if (hh < 0 || mm < 0) return false;
        out.hasTime = true;
        out.minute = hh * 60 + mm;
        out.utc = v.back() == 'Z';
    }
    return true;
}

int ParseOffsetMinutes(const std::string& v) {
    if (v.size() < 5) return 0;
    const int sign = v[0] == '-' ? -1 : 1;
    const int hh = ReadInt(v, 1, 2);
    const int mm = ReadInt(v, 3, 2);
    if (hh < 0 || mm < 0) return 0;
    return sign * (hh * 60 + mm);
}

int WeekdayFromCode(const std::string& code) {
    if (code == "SU") return 0;
    if (code == "MO") return 1;
    if (code == "TU") return 2;
    if (code == "WE") return 3;
    if (code == "TH") return 4;
    if (code == "FR") return 5;
    if (code == "SA") return 6;
    return -1;
}

void ParseRRule(const std::string& text, Recurrence& r) {
    size_t pos = 0;
    while (pos <= text.size()) {
        size_t semi = text.find(';', pos);
        if (semi == std::string::npos) semi = text.size();
        const std::string part = text.substr(pos, semi - pos);
        pos = semi + 1;

        const size_t eq = part.find('=');
        if (eq == std::string::npos) continue;
        const std::string key = part.substr(0, eq);
        const std::string val = part.substr(eq + 1);

        if (key == "FREQ") {
            if (val == "DAILY") r.freq = Freq::Daily;
            else if (val == "WEEKLY") r.freq = Freq::Weekly;
            else if (val == "MONTHLY") r.freq = Freq::Monthly;
            else if (val == "YEARLY") r.freq = Freq::Yearly;
        } else if (key == "INTERVAL") {
            r.interval = std::max(1, std::atoi(val.c_str()));
        } else if (key == "COUNT") {
            r.count = std::max(0, std::atoi(val.c_str()));
        } else if (key == "UNTIL") {
            IcsWall u;
            if (ParseIcsWall(val, u)) r.until = u.day;
        } else if (key == "BYDAY") {
            for (const std::string& tok : SplitList(val, ',')) {
                if (tok.size() < 2) continue;
                const int wd = WeekdayFromCode(tok.substr(tok.size() - 2));
                if (wd < 0) continue;
                ByDay b;
                b.weekday = wd;
                b.ordinal = std::atoi(tok.substr(0, tok.size() - 2).c_str());
                r.byDay.push_back(b);
            }
        } else if (key == "BYMONTHDAY") {
            for (const std::string& tok : SplitList(val, ',')) {
                if (!tok.empty()) r.byMonthDay.push_back(std::atoi(tok.c_str()));
            }
        } else if (key == "BYMONTH") {
            for (const std::string& tok : SplitList(val, ',')) {
                if (!tok.empty()) r.byMonth.push_back(std::atoi(tok.c_str()));
            }
        }
    }
}

bool IsExcluded(const CalEvent& ev, int64_t day) {
    return std::find(ev.excluded.begin(), ev.excluded.end(), day) != ev.excluded.end();
}

bool Matches(const CalEvent& ev, int64_t day) {
    const Recurrence& r = ev.rule;
    const int64_t diff = day - ev.startDay;
    switch (r.freq) {
        case Freq::Daily:
            return diff % r.interval == 0;

        case Freq::Weekly: {
            const int wd = Weekday(day);
            const int64_t startSunday = ev.startDay - ev.startWeekday;
            const int64_t daySunday = day - wd;
            const int64_t weeks = (daySunday - startSunday) / 7;
            if (weeks % r.interval != 0) return false;
            if (r.byDay.empty()) return wd == ev.startWeekday;
            for (const ByDay& b : r.byDay) {
                if (b.weekday == wd) return true;
            }
            return false;
        }

        case Freq::Monthly: {
            const Ymd ymd = CivilFromDays(day);
            const int64_t months = (ymd.y - ev.startYmd.y) * 12LL + (ymd.m - ev.startYmd.m);
            if (months % r.interval != 0) return false;
            if (!r.byDay.empty()) {
                const int dim = DaysInMonth(ymd.y, ymd.m);
                for (const ByDay& b : r.byDay) {
                    if (b.weekday != Weekday(day)) continue;
                    if (b.ordinal == 0) return true;
                    if (b.ordinal > 0 && (ymd.d - 1) / 7 + 1 == b.ordinal) return true;
                    if (b.ordinal < 0 && (dim - ymd.d) / 7 + 1 == -b.ordinal) return true;
                }
                return false;
            }
            if (!r.byMonthDay.empty()) {
                for (int md : r.byMonthDay) {
                    if (md == ymd.d) return true;
                }
                return false;
            }
            return ymd.d == ev.startYmd.d;
        }

        case Freq::Yearly: {
            const Ymd ymd = CivilFromDays(day);
            if ((ymd.y - ev.startYmd.y) % r.interval != 0) return false;
            return ymd.m == ev.startYmd.m && ymd.d == ev.startYmd.d;
        }

        case Freq::None:
        default:
            return day == ev.startDay;
    }
}

template <typename Fn>
void ForEachOccurrence(const CalEvent& ev, int64_t scanFrom, int64_t scanTo, Fn&& fn) {
    if (ev.rule.freq == Freq::None) {
        if (ev.startDay >= scanFrom && ev.startDay < scanTo && !IsExcluded(ev, ev.startDay)) {
            fn(ev.startDay);
        }
        return;
    }

    const int64_t last = std::min(scanTo - 1, ev.rule.until);
    // Without COUNT, each occurrence is decided by its date alone, so the scan can start at the
    // window instead of the event's first day.
    const int64_t from = ev.rule.count > 0 ? ev.startDay : std::max(ev.startDay, scanFrom);
    int count = 0;
    for (int64_t day = from; day <= last; ++day) {
        if (!Matches(ev, day) || IsExcluded(ev, day)) continue;
        ++count;
        if (ev.rule.count > 0 && count > ev.rule.count) break;
        if (day >= scanFrom) fn(day);
    }
}

// ── Calendar: time zones from the calendar file's VTIMEZONE blocks ──

void CollectTransitions(const TzDef& def, int year, std::vector<TzTransition>& out) {
    for (const TzRule& r : def.rules) {
        int64_t localMin = 0;
        if (r.rule.freq == Freq::None) {
            if (CivilFromDays(FloorDiv(r.startLocalMin, 1440)).y != year) continue;
            localMin = r.startLocalMin;
        } else {
            const Ymd start = CivilFromDays(FloorDiv(r.startLocalMin, 1440));
            if (year < start.y) continue;

            const int month = r.rule.byMonth.empty() ? start.m : r.rule.byMonth.front();
            const int64_t firstDay = DaysFromCivil(year, month, 1);
            int64_t day = DaysFromCivil(year, month, start.d);
            if (!r.rule.byDay.empty()) {
                const ByDay b = r.rule.byDay.front();
                if (b.ordinal >= 0) {
                    const int ord = b.ordinal == 0 ? 1 : b.ordinal;
                    day = firstDay + ((b.weekday - Weekday(firstDay) + 7) % 7) + 7 * (ord - 1);
                } else {
                    const int64_t lastDay = firstDay + DaysInMonth(year, month) - 1;
                    day = lastDay - ((Weekday(lastDay) - b.weekday + 7) % 7) + 7 * (b.ordinal + 1);
                }
            }
            localMin = day * 1440 + MinuteOfDay(r.startLocalMin);
        }
        out.push_back(TzTransition{localMin - r.offsetFrom, r.offsetFrom, r.offsetTo});
    }
}

int OffsetAtUtc(const TzDef& def, int64_t utcMin) {
    const int year = CivilFromDays(FloorDiv(utcMin, 1440)).y;
    std::vector<TzTransition> transitions;
    for (int y = year - 1; y <= year + 1; ++y) CollectTransitions(def, y, transitions);
    if (transitions.empty()) return 0;

    std::sort(transitions.begin(), transitions.end(),
              [](const TzTransition& a, const TzTransition& b) { return a.utcMin < b.utcMin; });
    int offset = transitions.front().offsetFrom;
    for (const TzTransition& t : transitions) {
        if (t.utcMin > utcMin) break;
        offset = t.offsetTo;
    }
    return offset;
}

int64_t LocalToUtc(const TzDef& def, int64_t wallMin) {
    std::vector<int> candidates;
    for (const TzRule& r : def.rules) {
        candidates.push_back(r.offsetFrom);
        candidates.push_back(r.offsetTo);
    }
    for (int c : candidates) {
        const int64_t utc = wallMin - c;
        if (OffsetAtUtc(def, utc) == c) return utc;
    }
    return wallMin - OffsetAtUtc(def, wallMin);
}

LocalStart UtcToPcLocal(int64_t utcMin) {
    const int64_t days = FloorDiv(utcMin, 1440);
    const int minute = static_cast<int>(utcMin - days * 1440);
    const Ymd ymd = CivilFromDays(days);

    SYSTEMTIME utc = {};
    utc.wYear = static_cast<WORD>(ymd.y);
    utc.wMonth = static_cast<WORD>(ymd.m);
    utc.wDay = static_cast<WORD>(ymd.d);
    utc.wHour = static_cast<WORD>(minute / 60);
    utc.wMinute = static_cast<WORD>(minute % 60);

    LocalStart out;
    SYSTEMTIME local = {};
    if (SystemTimeToTzSpecificLocalTime(nullptr, &utc, &local)) {
        out.day = DaysFromCivil(local.wYear, local.wMonth, local.wDay);
        out.minute = local.wHour * 60 + local.wMinute;
    } else {
        out.day = days;
        out.minute = minute;
    }
    return out;
}

LocalStart ToLocalStart(const CalEvent& ev, int64_t wallDay) {
    LocalStart out;
    out.day = wallDay;
    out.allDay = ev.allDay;
    out.minute = ev.allDay ? -1 : ev.startMinute;
    if (ev.allDay || (!ev.utc && !ev.tz)) return out;

    const int64_t wall = wallDay * 1440 + ev.startMinute;
    const int64_t utc = ev.utc ? wall : LocalToUtc(*ev.tz, wall);
    return UtcToPcLocal(utc);
}

using ZoneMap = std::map<std::string, std::shared_ptr<const TzDef>>;

ZoneMap ParseTimezones(const std::vector<std::string>& lines) {
    ZoneMap zones;
    bool inZone = false;
    bool inSub = false;
    std::string tzid;
    TzDef def;
    TzRule rule;

    for (const std::string& line : lines) {
        if (line == "BEGIN:VTIMEZONE") {
            inZone = true;
            tzid.clear();
            def = TzDef();
            continue;
        }
        if (line == "END:VTIMEZONE") {
            if (inZone && !tzid.empty() && !def.rules.empty()) {
                zones[tzid] = std::make_shared<const TzDef>(def);
            }
            inZone = false;
            continue;
        }
        if (!inZone) continue;
        if (line == "BEGIN:STANDARD" || line == "BEGIN:DAYLIGHT") {
            inSub = true;
            rule = TzRule();
            continue;
        }
        if (line == "END:STANDARD" || line == "END:DAYLIGHT") {
            if (inSub) def.rules.push_back(rule);
            inSub = false;
            continue;
        }

        IcsProp p;
        if (!SplitIcsProp(line, p)) continue;
        if (!inSub) {
            if (p.name == "TZID") tzid = p.value;
            continue;
        }
        if (p.name == "DTSTART") {
            IcsWall w;
            if (ParseIcsWall(p.value, w)) rule.startLocalMin = w.day * 1440 + w.minute;
        } else if (p.name == "TZOFFSETFROM") {
            rule.offsetFrom = ParseOffsetMinutes(p.value);
        } else if (p.name == "TZOFFSETTO") {
            rule.offsetTo = ParseOffsetMinutes(p.value);
        } else if (p.name == "RRULE") {
            ParseRRule(p.value, rule.rule);
        }
    }
    return zones;
}

// ── Calendar: events ──

void FinishEvent(const RawEvent& raw, const ZoneMap& zones, std::vector<CalEvent>& events,
                 std::vector<std::pair<std::string, int64_t>>& overrides) {
    if (raw.dtstart.empty()) return;

    IcsWall s;
    if (!ParseIcsWall(raw.dtstart, s)) return;

    if (!raw.recurrenceId.empty()) {
        IcsWall rid;
        if (ParseIcsWall(raw.recurrenceId, rid)) overrides.emplace_back(raw.uid, rid.day);
    }
    if (raw.cancelled) return;

    CalEvent ev;
    ev.uid = raw.uid;
    ev.summary = UnescapeIcsText(raw.summary);
    ev.startDay = s.day;
    ev.startYmd = CivilFromDays(s.day);
    ev.startWeekday = Weekday(s.day);
    ev.allDay = !s.hasTime;
    ev.startMinute = s.hasTime ? s.minute : 0;
    if (s.hasTime) {
        ev.utc = s.utc;
        if (!s.utc && !raw.dtstartTzid.empty()) {
            const auto it = zones.find(raw.dtstartTzid);
            if (it != zones.end()) ev.tz = it->second;
        }
    }

    int64_t endDay = s.day + 1;
    IcsWall e;
    if (!raw.dtend.empty() && ParseIcsWall(raw.dtend, e)) {
        endDay = e.day;
        if (e.hasTime && e.minute == 0 && endDay > s.day) endDay -= 1;
    }
    ev.durationDays = std::max<int64_t>(1, endDay - s.day);

    if (!raw.rrule.empty()) ParseRRule(raw.rrule, ev.rule);

    for (const std::string& list : raw.exdates) {
        for (const std::string& piece : SplitList(list, ',')) {
            IcsWall ex;
            if (ParseIcsWall(piece, ex)) ev.excluded.push_back(ex.day);
        }
    }

    events.push_back(ev);
}

std::vector<CalEvent> ParseIcsCalendar(const std::string& text) {
    const std::vector<std::string> lines = UnfoldIcsLines(text);
    const ZoneMap zones = ParseTimezones(lines);

    std::vector<CalEvent> events;
    std::vector<std::pair<std::string, int64_t>> overrides;

    bool inEvent = false;
    RawEvent raw;
    for (const std::string& line : lines) {
        if (line == "BEGIN:VEVENT") {
            inEvent = true;
            raw = RawEvent();
            continue;
        }
        if (line == "END:VEVENT") {
            inEvent = false;
            FinishEvent(raw, zones, events, overrides);
            continue;
        }
        if (!inEvent) continue;

        IcsProp p;
        if (!SplitIcsProp(line, p)) continue;

        if (p.name == "UID") raw.uid = p.value;
        else if (p.name == "SUMMARY") raw.summary = p.value;
        else if (p.name == "DTSTART") {
            raw.dtstart = p.value;
            raw.dtstartTzid = GetParam(p.params, "TZID");
        }
        else if (p.name == "DTEND") raw.dtend = p.value;
        else if (p.name == "RRULE") raw.rrule = p.value;
        else if (p.name == "EXDATE") raw.exdates.push_back(p.value);
        else if (p.name == "RECURRENCE-ID") raw.recurrenceId = p.value;
        else if (p.name == "STATUS") raw.cancelled = p.value == "CANCELLED";
    }

    for (CalEvent& ev : events) {
        if (ev.rule.freq == Freq::None) continue;
        for (const auto& o : overrides) {
            if (o.first == ev.uid) ev.excluded.push_back(o.second);
        }
    }
    return events;
}

std::vector<bool> BuildMonthMarks(const std::vector<CalEvent>& events, int year, int month) {
    const int dim = DaysInMonth(year, month);
    std::vector<bool> marks(static_cast<size_t>(dim), false);
    const int64_t rangeStart = DaysFromCivil(year, month, 1);
    const int64_t rangeEnd = rangeStart + dim;

    for (const CalEvent& ev : events) {
        ForEachOccurrence(ev, rangeStart - ev.durationDays - 3, rangeEnd + 3, [&](int64_t wallDay) {
            const LocalStart ls = ToLocalStart(ev, wallDay);
            for (int64_t k = 0; k < ev.durationDays; ++k) {
                const int64_t day = ls.day + k;
                if (day >= rangeStart && day < rangeEnd) {
                    marks[static_cast<size_t>(day - rangeStart)] = true;
                }
            }
        });
    }
    return marks;
}

std::vector<UpcomingItem> CollectUpcoming(const std::vector<CalEvent>& events,
                                          int64_t fromDay, int64_t toDay, size_t maxItems) {
    std::vector<UpcomingItem> items;
    for (const CalEvent& ev : events) {
        const std::wstring title = ev.summary.empty() ? L"(No title)" : Utf8ToWide(ev.summary);
        ForEachOccurrence(ev, fromDay - ev.durationDays - 3, toDay + 3, [&](int64_t wallDay) {
            const LocalStart ls = ToLocalStart(ev, wallDay);
            if (ls.day >= fromDay && ls.day < toDay) {
                items.push_back(UpcomingItem{ls.day, ls.minute, title});
            }
        });
    }
    std::stable_sort(items.begin(), items.end(), [](const UpcomingItem& a, const UpcomingItem& b) {
        return a.day != b.day ? a.day < b.day : a.minute < b.minute;
    });
    if (items.size() > maxItems) items.resize(maxItems);
    return items;
}

std::vector<std::vector<AgendaItem>> CollectAgenda(const std::vector<CalEvent>& events,
                                                   int64_t fromDay, int days) {
    std::vector<std::vector<AgendaItem>> buckets(static_cast<size_t>(days));
    for (const CalEvent& ev : events) {
        const std::wstring title = ev.summary.empty() ? L"(No title)" : Utf8ToWide(ev.summary);
        ForEachOccurrence(ev, fromDay - ev.durationDays - 3, fromDay + days + 3, [&](int64_t wallDay) {
            const LocalStart ls = ToLocalStart(ev, wallDay);
            for (int64_t k = 0; k < ev.durationDays; ++k) {
                const int64_t index = ls.day + k - fromDay;
                if (index < 0 || index >= days) continue;
                buckets[static_cast<size_t>(index)].push_back(AgendaItem{ls.minute, ls.allDay, title});
            }
        });
    }
    for (auto& bucket : buckets) {
        std::stable_sort(bucket.begin(), bucket.end(), [](const AgendaItem& a, const AgendaItem& b) {
            return a.minute < b.minute;
        });
    }
    return buckets;
}

// ── RSS / Atom parsing ──

std::string DecodeXmlText(std::string value) {
    struct Entity { const char* from; const char* to; } entities[] = {
        {"&amp;", "&"}, {"&lt;", "<"}, {"&gt;", ">"}, {"&quot;", "\""},
        {"&apos;", "'"}, {"&#39;", "'"}, {"&#x27;", "'"}, {"&nbsp;", " "}
    };
    for (const auto& e : entities) {
        size_t p = 0; while ((p = value.find(e.from, p)) != std::string::npos) {
            value.replace(p, std::strlen(e.from), e.to); p += std::strlen(e.to);
        }
    }
    // Strip embedded markup (descriptions commonly contain HTML).
    std::string plain; plain.reserve(value.size()); bool inTag = false;
    for (char c : value) { if (c == '<') inTag = true; else if (c == '>') inTag = false; else if (!inTag) plain.push_back(c); }
    return plain;
}

std::string XmlTagValue(const std::string& block, const char* tag) {
    const std::string open = std::string("<") + tag;
    size_t p = block.find(open);
    if (p == std::string::npos) return {};
    p = block.find('>', p);
    if (p == std::string::npos) return {};
    ++p;
    const std::string close = std::string("</") + tag + ">";
    size_t e = block.find(close, p);
    if (e == std::string::npos) return {};
    std::string v = block.substr(p, e - p);
    const size_t c1 = v.find("<![CDATA[");
    if (c1 != std::string::npos) { const size_t c2 = v.find("]]>", c1 + 9); if (c2 != std::string::npos) v = v.substr(c1 + 9, c2 - c1 - 9); }
    return DecodeXmlText(v);
}

// Extract the feed-level title, not an individual item's title. RSS 2.0
// stores it under <channel>; Atom stores it directly under <feed>.
std::wstring ParseRssFeedTitle(const std::string& xml) {
    std::string title;
    const size_t channelStart = xml.find("<channel");
    if (channelStart != std::string::npos) {
        const size_t channelOpenEnd = xml.find('>', channelStart);
        const size_t channelEnd = xml.find("</channel>", channelOpenEnd == std::string::npos ? channelStart : channelOpenEnd + 1);
        if (channelOpenEnd != std::string::npos && channelEnd != std::string::npos)
            title = XmlTagValue(xml.substr(channelOpenEnd + 1, channelEnd - channelOpenEnd - 1), "title");
    }
    if (title.empty()) {
        // For Atom, the feed-level title precedes the first entry.
        const size_t feedStart = xml.find("<feed");
        if (feedStart != std::string::npos) {
            const size_t feedOpenEnd = xml.find('>', feedStart);
            const size_t entryStart = xml.find("<entry", feedOpenEnd == std::string::npos ? feedStart : feedOpenEnd + 1);
            if (feedOpenEnd != std::string::npos) {
                const size_t end = entryStart == std::string::npos ? xml.size() : entryStart;
                title = XmlTagValue(xml.substr(feedOpenEnd + 1, end - feedOpenEnd - 1), "title");
            }
        }
    }
    return Utf8ToWide(title);
}

std::vector<RssItem> ParseRss(const std::string& xml, int limit) {
    std::vector<RssItem> items; items.reserve(static_cast<size_t>(limit));
    size_t pos = 0;
    while (items.size() < static_cast<size_t>(limit)) {
        size_t a = xml.find("<item", pos), b = xml.find("<entry", pos);
        if (a == std::string::npos && b == std::string::npos) break;
        const bool atom = b != std::string::npos && (a == std::string::npos || b < a);
        const size_t start = atom ? b : a;
        const size_t openEnd = xml.find('>', start);
        if (openEnd == std::string::npos) break;
        const char* closeTag = atom ? "</entry>" : "</item>";
        const size_t end = xml.find(closeTag, openEnd + 1);
        if (end == std::string::npos) break;
        const std::string block = xml.substr(openEnd + 1, end - openEnd - 1);
        RssItem item;
        item.title = Utf8ToWide(XmlTagValue(block, "title"));
        if (atom) {
            size_t lp = block.find("<link");
            if (lp != std::string::npos) {
                size_t le = block.find('>', lp);
                if (le != std::string::npos) {
                    std::string tag = block.substr(lp, le - lp + 1);
                    size_t hp = tag.find("href=");
                    if (hp != std::string::npos) { ++hp; if (hp < tag.size() && (tag[hp] == '\"' || tag[hp] == '\'')) { char q = tag[hp++]; size_t qe = tag.find(q, hp); if (qe != std::string::npos) item.link = Utf8ToWide(tag.substr(hp, qe - hp)); } }
                }
            }
        } else item.link = Utf8ToWide(XmlTagValue(block, "link"));
        if (!item.title.empty()) items.push_back(std::move(item));
        pos = end + std::strlen(closeTag);
    }
    return items;
}

void FetchRssOnce(const RssConfig& cfg) {
    if (cfg.url.rfind(L"https://", 0) != 0 && cfg.url.rfind(L"http://", 0) != 0) {
        std::lock_guard<std::mutex> lock(g_mutex); g_rssStatus = FetchStatus::Failed; return;
    }
    const WH_URL_CONTENT* content = Wh_GetUrlContent(cfg.url.c_str(), nullptr);
    if (!content || content->statusCode != 200 || !content->data || content->length == 0 || content->length > 5 * 1024 * 1024) {
        if (content) Wh_FreeUrlContent(content);
        std::lock_guard<std::mutex> lock(g_mutex); g_rssStatus = FetchStatus::Failed; return;
    }
    const std::string xml(content->data, content->length);
    Wh_FreeUrlContent(content);
    const std::wstring feedTitle = ParseRssFeedTitle(xml);
    auto parsed = std::make_shared<const std::vector<RssItem>>(ParseRss(xml, cfg.maxItems));
    { std::lock_guard<std::mutex> lock(g_mutex); g_rssFeedTitle = feedTitle; g_rssItems = parsed; g_rssStatus = FetchStatus::Ok; }
    g_rssScroll = 0;
    Wh_Log(L"RSS feed loaded: %u items", static_cast<unsigned>(parsed->size()));
}

DWORD WINAPI RssThreadProc(LPVOID) {
    for (int i = 0; i < 50 && !g_hwnd && !g_stopping; ++i) Sleep(100);
    while (!g_stopping) {
        const RssConfig cfg = SnapshotRss();
        if (cfg.url.empty()) { std::lock_guard<std::mutex> lock(g_mutex); g_rssStatus = FetchStatus::NoUrl; }
        else FetchRssOnce(cfg);
        if (g_hwnd) PostMessageW(g_hwnd, kRssUpdatedMessage, 0, 0);
        WaitForSingleObject(g_rssWake, static_cast<DWORD>(cfg.refreshMinutes) * 60000u);
    }
    return 0;
}

// ── Downloads ──

void SetCalendarStatus(FetchStatus status) {
    std::lock_guard<std::mutex> lock(g_mutex);
    g_calStatus = status;
}

void FetchCalendarOnce(const CalendarConfig& cfg) {
    const WH_URL_CONTENT* content = Wh_GetUrlContent(cfg.url.c_str(), nullptr);
    if (!content) {
        Wh_Log(L"Calendar fetch failed (no response)");
        SetCalendarStatus(FetchStatus::Failed);
        return;
    }
    if (content->statusCode != 200 || !content->data || content->length == 0) {
        Wh_Log(L"Calendar fetch failed (HTTP %d)", content->statusCode);
        Wh_FreeUrlContent(content);
        SetCalendarStatus(FetchStatus::Failed);
        return;
    }

    const std::string text(content->data, content->length);
    Wh_FreeUrlContent(content);

    auto parsed = std::make_shared<const std::vector<CalEvent>>(ParseIcsCalendar(text));
    {
        std::lock_guard<std::mutex> lock(g_mutex);
        g_events = parsed;
        ++g_eventsVersion;
        g_calStatus = FetchStatus::Ok;
    }
    Wh_Log(L"Calendar loaded: %u events", static_cast<unsigned>(parsed->size()));
}

DWORD WINAPI CalendarThreadProc(LPVOID) {
    for (int i = 0; i < 50 && !g_hwnd && !g_stopping; ++i) Sleep(100);

    while (!g_stopping) {
        const CalendarConfig cfg = SnapshotCalendar();
        if (cfg.url.empty()) {
            SetCalendarStatus(FetchStatus::NoUrl);
        } else {
            FetchCalendarOnce(cfg);
        }
        if (g_hwnd) PostMessageW(g_hwnd, kCalendarUpdatedMessage, 0, 0);

        WaitForSingleObject(g_calendarWake, static_cast<DWORD>(cfg.refreshMinutes) * 60000u);
    }
    return 0;
}

DWORD WINAPI WeatherThreadProc(LPVOID) {
    for (int i = 0; i < 50 && !g_hwnd && !g_stopping; ++i) Sleep(100);

    while (!g_stopping) {
        const WeatherConfig cfg = SnapshotWeather();

        WeatherData data;
        const bool ok = FetchForecast(cfg, data);
        {
            std::lock_guard<std::mutex> lock(g_mutex);
            if (ok) {
                g_weather = std::move(data);
            } else if (!g_weather.valid) {
                g_weather.failed = true;
            }
        }
        if (g_hwnd) PostMessageW(g_hwnd, kWeatherUpdatedMessage, 0, 0);

        const DWORD waitMs = ok ? static_cast<DWORD>(cfg.refreshMinutes) * 60000u : 60000u;
        WaitForSingleObject(g_weatherWake, waitMs);
    }
    return 0;
}

// ── Drawing helpers ──

void FillEllipseF(Graphics& g, Brush* brush, float x, float y, float w, float h) {
    g.FillEllipse(brush, static_cast<REAL>(x), static_cast<REAL>(y),
                  static_cast<REAL>(w), static_cast<REAL>(h));
}

void DrawRoundedRectangle(Graphics& g, const RectF& rc, float radius,
                          const Brush& brush, const Pen* pen = nullptr) {
    GraphicsPath path;
    const float d = radius * 2.0f;
    path.AddArc(rc.X, rc.Y, d, d, 180, 90);
    path.AddArc(rc.X + rc.Width - d, rc.Y, d, d, 270, 90);
    path.AddArc(rc.X + rc.Width - d, rc.Y + rc.Height - d, d, d, 0, 90);
    path.AddArc(rc.X, rc.Y + rc.Height - d, d, d, 90, 90);
    path.CloseFigure();
    g.FillPath(&brush, &path);
    if (pen) g.DrawPath(pen, &path);
}

void DrawGlassPanel(Graphics& g, const RectF& rc, float radius) {
    DrawRoundedRectangle(g, RectF(rc.X, rc.Y + 4.0f, rc.Width, rc.Height), radius,
                         SolidBrush(Color(60, 0, 0, 0)));

    LinearGradientBrush body(PointF(rc.X, rc.Y), PointF(rc.X, rc.Y + rc.Height),
                             Color(120, 26, 32, 44), Color(175, 88, 98, 116));
    DrawRoundedRectangle(g, rc, radius, body);

    RectF sheenRc(rc.X + 4.0f, rc.Y + 4.0f, rc.Width - 8.0f, rc.Height * 0.40f);
    LinearGradientBrush sheen(PointF(0.0f, sheenRc.Y), PointF(0.0f, sheenRc.Y + sheenRc.Height),
                              Color(60, 255, 255, 255), Color(0, 255, 255, 255));
    DrawRoundedRectangle(g, sheenRc, radius - 4.0f, sheen);

    SolidBrush none(Color(0, 0, 0, 0));
    Pen inner(Color(60, 255, 255, 255), 1.0f);
    DrawRoundedRectangle(g, RectF(rc.X + 3.0f, rc.Y + 3.0f, rc.Width - 6.0f, rc.Height - 6.0f),
                         radius - 3.0f, none, &inner);
    Pen outer(Color(170, 255, 255, 255), 1.25f);
    DrawRoundedRectangle(g, rc, radius, none, &outer);
    Pen accent(Color(110, 150, 200, 255), 1.5f);
    g.DrawLine(&accent, rc.X + radius, rc.Y + rc.Height - 1.0f,
               rc.X + rc.Width - radius, rc.Y + rc.Height - 1.0f);
}

void DrawDarkPanel(Graphics& g, const RectF& rc, float radius) {
    DrawRoundedRectangle(g, RectF(rc.X, rc.Y + 4.0f, rc.Width, rc.Height), radius,
                         SolidBrush(Color(60, 0, 0, 0)));
    DrawRoundedRectangle(g, rc, radius, SolidBrush(Color(255, 28, 28, 30)));
}

void DrawLightPanel(Graphics& g, const RectF& rc, float radius) {
    DrawRoundedRectangle(g, RectF(rc.X, rc.Y + 4.0f, rc.Width, rc.Height), radius,
                         SolidBrush(Color(60, 0, 0, 0)));
    DrawRoundedRectangle(g, rc, radius, SolidBrush(Color(255, 242, 242, 246)));
}

void DrawLabel(Graphics& g, const wchar_t* text, FontFamily& family, float size,
               FontStyle style, RectF rc, StringAlignment horizontal,
               StringAlignment vertical, Color color) {
    Font font(&family, size, style, UnitPixel);
    StringFormat format;
    format.SetAlignment(horizontal);
    format.SetLineAlignment(vertical);
    format.SetFormatFlags(StringFormatFlagsNoWrap);
    format.SetTrimming(StringTrimmingEllipsisCharacter);

    const bool darkText = color.GetR() < 128;
    SolidBrush shadow(darkText ? Color(70, 255, 255, 255) : Color(90, 0, 0, 0));
    RectF shadowRc(rc.X, rc.Y + 1.0f, rc.Width, rc.Height);
    g.DrawString(text, -1, &font, shadowRc, &format, &shadow);

    SolidBrush brush(color);
    g.DrawString(text, -1, &font, rc, &format, &brush);
}

// RSS typography uses a configurable foreground color and a restrained,
// configurable drop shadow. A few low-alpha offset passes soften the shadow
// without producing the heavy outline/halo used by the earlier renderer.
void DrawRssLabel(Graphics& g, const wchar_t* text, FontFamily& family, float size,
                  FontStyle style, const RectF& rc, Color color, int shadowIntensity) {
    Font font(&family, size, style, UnitPixel);
    StringFormat format;
    format.SetAlignment(StringAlignmentNear);
    format.SetLineAlignment(StringAlignmentCenter);
    format.SetFormatFlags(StringFormatFlagsNoWrap);
    format.SetTrimming(StringTrimmingEllipsisCharacter);

    const BYTE alpha = static_cast<BYTE>(std::clamp(shadowIntensity, 0, 100) * 0.72f);
    if (alpha > 0) {
        SolidBrush shadow(Color(alpha, 0, 0, 0));
        const float offsets[][2] = {{0.0f, 1.0f}, {1.0f, 1.0f}, {-1.0f, 1.0f}};
        for (const auto& d : offsets) {
            RectF shadowRc(rc.X + d[0], rc.Y + d[1], rc.Width, rc.Height);
            g.DrawString(text, -1, &font, shadowRc, &format, &shadow);
        }
    }
    SolidBrush brush(color);
    g.DrawString(text, -1, &font, rc, &format, &brush);
}

void DrawRssRowText(Graphics& g, const wchar_t* text, FontFamily& family,
                    const RectF& rc, Color color, int shadowIntensity) {
    Font font(&family, 9.5f, FontStyleRegular, UnitPixel);
    StringFormat format;
    format.SetAlignment(StringAlignmentNear);
    format.SetLineAlignment(StringAlignmentCenter);
    format.SetTrimming(StringTrimmingEllipsisCharacter);
    format.SetFormatFlags(StringFormatFlagsLineLimit);

    const BYTE alpha = static_cast<BYTE>(std::clamp(shadowIntensity, 0, 100) * 0.72f);
    if (alpha > 0) {
        SolidBrush shadow(Color(alpha, 0, 0, 0));
        const float offsets[][2] = {{0.0f, 1.0f}, {1.0f, 1.0f}, {-1.0f, 1.0f}};
        for (const auto& d : offsets) {
            RectF shadowRc(rc.X + d[0], rc.Y + d[1], rc.Width, rc.Height);
            g.DrawString(text, -1, &font, shadowRc, &format, &shadow);
        }
    }
    SolidBrush brush(color);
    g.DrawString(text, -1, &font, rc, &format, &brush);
}

// ── Weather drawing ──

WeatherIcon IconForCode(int code) {
    if (code == 0) return WeatherIcon::Clear;
    if (code == 1 || code == 2) return WeatherIcon::PartlyCloudy;
    if (code == 3) return WeatherIcon::Cloudy;
    if (code == 45 || code == 48) return WeatherIcon::Fog;
    if ((code >= 51 && code <= 67) || (code >= 80 && code <= 82)) return WeatherIcon::Rain;
    if ((code >= 71 && code <= 77) || (code >= 85 && code <= 86)) return WeatherIcon::Snow;
    if (code >= 95) return WeatherIcon::Storm;
    return WeatherIcon::Cloudy;
}

const wchar_t* ConditionText(int code) {
    if (code == 0) return L"Clear";
    if (code == 1) return L"Mostly clear";
    if (code == 2) return L"Partly cloudy";
    if (code == 3) return L"Overcast";
    if (code == 45 || code == 48) return L"Fog";
    if (code >= 51 && code <= 57) return L"Drizzle";
    if (code >= 61 && code <= 67) return L"Rain";
    if (code >= 71 && code <= 77) return L"Snow";
    if (code >= 80 && code <= 82) return L"Showers";
    if (code == 85 || code == 86) return L"Snow showers";
    if (code >= 95) return L"Thunderstorm";
    return L"Cloudy";
}

void HourLabel(const std::string& iso, wchar_t* out, size_t count) {
    const int hour = std::atoi(iso.c_str() + 11);
    const int hour12 = hour % 12 == 0 ? 12 : hour % 12;
    swprintf_s(out, count, L"%d %ls", hour12, hour < 12 ? L"AM" : L"PM");
}

void DrawCloud(Graphics& g, float cx, float cy, float w, Color color) {
    SolidBrush brush(color);
    const float h = w * 0.32f;
    DrawRoundedRectangle(g, RectF(cx - w * 0.5f, cy - h * 0.5f + w * 0.12f, w, h), h * 0.5f, brush);
    FillEllipseF(g, &brush, cx - w * 0.30f, cy - w * 0.22f, w * 0.34f, w * 0.34f);
    FillEllipseF(g, &brush, cx - w * 0.04f, cy - w * 0.40f, w * 0.48f, w * 0.48f);
    FillEllipseF(g, &brush, cx + w * 0.18f, cy - w * 0.14f, w * 0.30f, w * 0.30f);
}

void DrawSun(Graphics& g, float cx, float cy, float r, Color color) {
    SolidBrush brush(color);
    FillEllipseF(g, &brush, cx - r, cy - r, r * 2.0f, r * 2.0f);

    Pen ray(color, r * 0.22f);
    ray.SetStartCap(LineCapRound);
    ray.SetEndCap(LineCapRound);
    for (int i = 0; i < 8; ++i) {
        const float angle = kPiF * 2.0f * i / 8.0f;
        const float dx = std::cos(angle);
        const float dy = std::sin(angle);
        g.DrawLine(&ray, cx + dx * r * 1.35f, cy + dy * r * 1.35f,
                   cx + dx * r * 1.80f, cy + dy * r * 1.80f);
    }
}

void DrawWeatherIcon(Graphics& g, WeatherIcon icon, float cx, float cy, float s, Color cloud) {
    const Color sun(255, 255, 210, 80);
    const Color bolt(255, 255, 214, 60);
    const Color drop(255, 150, 200, 255);

    switch (icon) {
        case WeatherIcon::Clear:
            DrawSun(g, cx, cy, s * 0.26f, sun);
            break;
        case WeatherIcon::PartlyCloudy:
            DrawSun(g, cx - s * 0.14f, cy - s * 0.14f, s * 0.20f, sun);
            DrawCloud(g, cx + s * 0.08f, cy + s * 0.08f, s * 0.80f, cloud);
            break;
        case WeatherIcon::Cloudy:
            DrawCloud(g, cx, cy, s * 0.95f, cloud);
            break;
        case WeatherIcon::Fog: {
            SolidBrush brush(cloud);
            for (int i = -1; i <= 1; ++i) {
                DrawRoundedRectangle(g,
                    RectF(cx - s * 0.40f, cy + i * s * 0.20f - s * 0.04f, s * 0.80f, s * 0.08f),
                    s * 0.04f, brush);
            }
            break;
        }
        case WeatherIcon::Rain: {
            DrawCloud(g, cx, cy - s * 0.14f, s * 0.80f, cloud);
            Pen pen(drop, s * 0.06f);
            pen.SetStartCap(LineCapRound);
            pen.SetEndCap(LineCapRound);
            for (float off : {-0.20f, 0.0f, 0.20f}) {
                g.DrawLine(&pen, cx + off * s, cy + s * 0.16f,
                           cx + off * s - s * 0.05f, cy + s * 0.34f);
            }
            break;
        }
        case WeatherIcon::Snow: {
            DrawCloud(g, cx, cy - s * 0.14f, s * 0.80f, cloud);
            SolidBrush brush(cloud);
            for (float off : {-0.20f, 0.0f, 0.20f}) {
                FillEllipseF(g, &brush, cx + off * s - s * 0.05f, cy + s * 0.26f - s * 0.05f,
                             s * 0.10f, s * 0.10f);
            }
            break;
        }
        case WeatherIcon::Storm: {
            DrawCloud(g, cx, cy - s * 0.14f, s * 0.80f, cloud);
            const float by = cy + s * 0.10f;
            PointF points[] = {
                PointF(cx + s * 0.06f, by - s * 0.02f),
                PointF(cx - s * 0.08f, by + s * 0.16f),
                PointF(cx + s * 0.00f, by + s * 0.16f),
                PointF(cx - s * 0.05f, by + s * 0.32f),
                PointF(cx + s * 0.10f, by + s * 0.10f),
                PointF(cx + s * 0.02f, by + s * 0.10f),
            };
            SolidBrush brush(bolt);
            g.FillPolygon(&brush, points, ARRAYSIZE(points));
            break;
        }
    }
}

const wchar_t* WeekdayShortFromIso(const std::string& iso) {
    // Gregorian weekday calculation; ISO dates are supplied as YYYY-MM-DD.
    if (iso.size() < 10) return L"---";
    const int y0 = std::atoi(iso.substr(0, 4).c_str());
    const int m = std::atoi(iso.substr(5, 2).c_str());
    const int d = std::atoi(iso.substr(8, 2).c_str());
    if (y0 < 1 || m < 1 || m > 12 || d < 1 || d > 31) return L"---";
    static const int offsets[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    int y = y0;
    if (m < 3) --y;
    const int weekday = (y + y / 4 - y / 100 + y / 400 + offsets[m - 1] + d) % 7;
    static const wchar_t* names[] = {L"Sun", L"Mon", L"Tues", L"Wed", L"Thu", L"Fri", L"Sat"};
    return names[weekday];
}

void DrawWeatherWidget(Graphics& g, const RectF& rc, const WeatherConfig& cfg,
                       const WeatherData& data, bool darkText) {
    FontFamily sans(L"Segoe UI");
    FontFamily light(L"Segoe UI Light");
    const Color white = darkText ? Color(245, 22, 26, 34) : Color(245, 255, 255, 255);
    const Color soft = darkText ? Color(200, 22, 26, 34) : Color(200, 255, 255, 255);

    if (!data.valid) {
        DrawLabel(g, data.failed ? L"Weather unavailable" : L"Loading weather...",
                  sans, 11, FontStyleRegular, rc,
                  StringAlignmentCenter, StringAlignmentCenter, soft);
        return;
    }


    if (cfg.layout == 1) {
        const float left = rc.X + 14.0f;
        DrawLabel(g, cfg.label.c_str(), sans, 11, FontStyleBold,
                  RectF(left, rc.Y + 9, rc.Width - 28, 14),
                  StringAlignmentNear, StringAlignmentCenter, white);
        wchar_t temp[24]; swprintf_s(temp, L"%d\u00B0", (int)std::lround(data.currentTemp));
        DrawLabel(g, temp, light, 43, FontStyleRegular,
                  RectF(left - 2, rc.Y + 25, 115, 48),
                  StringAlignmentNear, StringAlignmentCenter, white);
        DrawWeatherIcon(g, IconForCode(data.currentCode), rc.X + rc.Width - 43, rc.Y + 45, 38, white);
        DrawLabel(g, ConditionText(data.currentCode), sans, 9, FontStyleBold,
                  RectF(rc.X + 125, rc.Y + 58, rc.Width - 140, 13),
                  StringAlignmentFar, StringAlignmentCenter, soft);
        const float top = rc.Y + 105;
        const float col = (rc.Width - 28) / 4.0f;
        const wchar_t* labels[] = {L"HIGH", L"LOW", L"PRECIP", L"WIND"};
        wchar_t values[4][32];
        swprintf_s(values[0], L"%d\u00B0", (int)std::lround(data.dailyHigh));
        swprintf_s(values[1], L"%d\u00B0", (int)std::lround(data.dailyLow));
        swprintf_s(values[2], L"%.1f mm", data.dailyPrecipitation);
        swprintf_s(values[3], L"%.0f km/h", data.dailyWind);
        for (int i=0;i<4;++i) {
            const float x = left + i * col;
            DrawLabel(g, labels[i], sans, 7.5f, FontStyleBold, RectF(x, top, col, 11),
                      StringAlignmentCenter, StringAlignmentCenter, soft);
            DrawLabel(g, values[i], sans, 10, FontStyleBold, RectF(x, top+15, col, 16),
                      StringAlignmentCenter, StringAlignmentCenter, white);
        }
        return;
    }

    if (cfg.layout == 2) {
        const float left = rc.X + 13.0f;
        DrawLabel(g, cfg.label.c_str(), sans, 11, FontStyleBold,
                  RectF(left, rc.Y + 8, rc.Width - 26, 14),
                  StringAlignmentNear, StringAlignmentCenter, white);
        // Six upcoming hourly conditions in a compact horizontal strip.
        const float colW = (rc.Width - 26.0f) / 6.0f;
        for (size_t i=0; i<std::min<size_t>(6, data.hours.size()); ++i) {
            const auto& h = data.hours[i];
            const float cx = left + colW * (i + 0.5f);
            wchar_t label[16], value[16]; HourLabel(h.time, label, ARRAYSIZE(label));
            swprintf_s(value, L"%d\u00B0", (int)std::lround(h.temp));
            DrawLabel(g, label, sans, 7.5f, FontStyleRegular, RectF(cx-colW/2, rc.Y+27, colW, 11),
                      StringAlignmentCenter, StringAlignmentCenter, soft);
            DrawWeatherIcon(g, IconForCode(h.code), cx, rc.Y+51, 17, white);
            DrawLabel(g, value, sans, 8.5f, FontStyleBold, RectF(cx-colW/2, rc.Y+63, colW, 12),
                      StringAlignmentCenter, StringAlignmentCenter, white);
        }
        Pen separator(Color(75,255,255,255), 1.0f);
        g.DrawLine(&separator, left, rc.Y+82, rc.GetRight()-13, rc.Y+82);
        DrawLabel(g, L"5-DAY FORECAST", sans, 8, FontStyleBold,
                  RectF(left, rc.Y+87, rc.Width-26, 12), StringAlignmentNear, StringAlignmentCenter, soft);
        // Scale every daily low/high range against the full five-day temperature
        // envelope. The colored segment is the day's own low-to-high interval.
        double forecastMin = data.days.empty() ? 0.0 : data.days.front().low;
        double forecastMax = data.days.empty() ? 1.0 : data.days.front().high;
        for (const auto& day : data.days) {
            forecastMin = std::min(forecastMin, day.low);
            forecastMax = std::max(forecastMax, day.high);
        }
        const double forecastSpan = std::max(1.0, forecastMax - forecastMin);
        for (size_t i=0; i<std::min<size_t>(5, data.days.size()); ++i) {
            const auto& d = data.days[i];
            const float y = rc.Y + 105 + static_cast<float>(i)*29.0f;
            DrawLabel(g, WeekdayShortFromIso(d.date), sans, 8.5f, FontStyleBold,
                      RectF(left, y, 34, 16), StringAlignmentNear, StringAlignmentCenter, white);
            DrawWeatherIcon(g, IconForCode(d.code), left+45, y+8, 16, white);

            wchar_t highText[20], lowText[20];
            swprintf_s(highText, L"%d\u00B0", (int)std::lround(d.high));
            swprintf_s(lowText, L"%d\u00B0", (int)std::lround(d.low));
            DrawLabel(g, highText, sans, 8.5f, FontStyleBold,
                      RectF(left+59, y, 31, 16), StringAlignmentCenter, StringAlignmentCenter, white);

            const float barX = left + 94.0f;
            const float barY = y + 7.0f;
            const float barW = std::max(36.0f, rc.GetRight() - 48.0f - barX);
            const float barH = 4.0f;
            const float lowPos = static_cast<float>((d.low - forecastMin) / forecastSpan);
            const float highPos = static_cast<float>((d.high - forecastMin) / forecastSpan);
            const float segX = barX + barW * std::clamp(lowPos, 0.0f, 1.0f);
            const float segRight = barX + barW * std::clamp(highPos, 0.0f, 1.0f);
            SolidBrush track(Color(75, 255, 255, 255));
            SolidBrush range(Color(235, 255, 190, 95));
            g.FillRectangle(&track, RectF(barX, barY, barW, barH));
            g.FillRectangle(&range, RectF(segX, barY, std::max(3.0f, segRight-segX), barH));
            FillEllipseF(g, &range, segX-2.0f, barY-1.0f, 6.0f, 6.0f);
            FillEllipseF(g, &range, segRight-2.0f, barY-1.0f, 6.0f, 6.0f);

            DrawLabel(g, lowText, sans, 8.5f, FontStyleRegular,
                      RectF(rc.GetRight()-43.0f, y, 30, 16), StringAlignmentFar, StringAlignmentCenter, soft);
        }
        return;
    }

    constexpr float kWPadX = 14.0f;
    constexpr float kRightColW = 120.0f;
    const float left = rc.X + kWPadX;
    const float right = rc.X + rc.Width - kWPadX;

    DrawLabel(g, cfg.label.c_str(), sans, 10, FontStyleBold,
              RectF(left, rc.Y + 12.0f, 150.0f, 14.0f),
              StringAlignmentNear, StringAlignmentCenter, white);

    wchar_t temp[16];
    swprintf_s(temp, L"%d\u00B0", static_cast<int>(std::lround(data.currentTemp)));
    DrawLabel(g, temp, light, 42, FontStyleRegular,
              RectF(left - 1.0f, rc.Y + 25.0f, 120.0f, 40.0f),
              StringAlignmentNear, StringAlignmentCenter, white);

    DrawWeatherIcon(g, IconForCode(data.currentCode), right - 19.0f, rc.Y + 26.0f, 40.0f, white);
    DrawLabel(g, ConditionText(data.currentCode), sans, 10, FontStyleBold,
              RectF(right - kRightColW, rc.Y + 42.0f, kRightColW, 13.0f),
              StringAlignmentFar, StringAlignmentCenter, white);

    wchar_t hiLo[48];
    swprintf_s(hiLo, L"H:%d\u00B0  L:%d\u00B0",
               static_cast<int>(std::lround(data.dailyHigh)),
               static_cast<int>(std::lround(data.dailyLow)));
    DrawLabel(g, hiLo, sans, 9, FontStyleRegular,
              RectF(right - kRightColW, rc.Y + 56.0f, kRightColW, 12.0f),
              StringAlignmentFar, StringAlignmentCenter, soft);

    const float colW = (rc.Width - 2.0f * kWPadX) / 6.0f;
    const size_t count = std::min<size_t>(6, data.hours.size());
    for (size_t i = 0; i < count; ++i) {
        const HourForecast& h = data.hours[i];
        const float cx = left + colW * (static_cast<float>(i) + 0.5f);

        wchar_t hourText[16];
        HourLabel(h.time, hourText, ARRAYSIZE(hourText));
        DrawLabel(g, hourText, sans, 9, FontStyleRegular,
                  RectF(cx - colW / 2.0f, rc.Y + 84.0f, colW, 12.0f),
                  StringAlignmentCenter, StringAlignmentCenter, soft);

        DrawWeatherIcon(g, IconForCode(h.code), cx, rc.Y + 109.0f, 22.0f, white);

        wchar_t tempText[16];
        swprintf_s(tempText, L"%d\u00B0", static_cast<int>(std::lround(h.temp)));
        DrawLabel(g, tempText, sans, 10, FontStyleRegular,
                  RectF(cx - colW / 2.0f, rc.Y + 120.0f, colW, 13.0f),
                  StringAlignmentCenter, StringAlignmentCenter, white);
    }
}

// ── Wallpaper under the widgets ──

template <typename T>
void SafeRelease(T*& p) {
    if (p) {
        p->Release();
        p = nullptr;
    }
}

std::wstring ReadRegString(const wchar_t* subkey, const wchar_t* value) {
    DWORD bytes = 0;
    if (RegGetValueW(HKEY_CURRENT_USER, subkey, value, RRF_RT_REG_SZ, nullptr, nullptr, &bytes) != ERROR_SUCCESS ||
        bytes < sizeof(wchar_t)) {
        return L"";
    }
    std::vector<wchar_t> buf(bytes / sizeof(wchar_t) + 1, L'\0');
    if (RegGetValueW(HKEY_CURRENT_USER, subkey, value, RRF_RT_REG_SZ, nullptr, buf.data(), &bytes) != ERROR_SUCCESS) {
        return L"";
    }
    return buf.data();
}

std::wstring ExpandEnv(const std::wstring& in) {
    if (in.empty()) return in;
    wchar_t out[MAX_PATH * 2];
    const DWORD n = ExpandEnvironmentStringsW(in.c_str(), out, ARRAYSIZE(out));
    if (n == 0 || n > ARRAYSIZE(out)) return in;
    return out;
}

std::wstring FileStamp(const std::wstring& path) {
    if (path.empty()) return L"";
    WIN32_FILE_ATTRIBUTE_DATA fad = {};
    if (!GetFileAttributesExW(path.c_str(), GetFileExInfoStandard, &fad)) return L"";
    return std::to_wstring(fad.ftLastWriteTime.dwHighDateTime) + L"." +
           std::to_wstring(fad.ftLastWriteTime.dwLowDateTime) + L"." +
           std::to_wstring(fad.nFileSizeLow);
}

Bitmap* LoadWallpaperFile(const std::wstring& path) {
    HANDLE file = CreateFileW(path.c_str(), GENERIC_READ,
                              FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                              nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE) return nullptr;

    LARGE_INTEGER size = {};
    if (!GetFileSizeEx(file, &size) || size.QuadPart <= 0 || size.QuadPart > 200LL * 1024 * 1024) {
        CloseHandle(file);
        return nullptr;
    }

    HGLOBAL mem = GlobalAlloc(GMEM_MOVEABLE, static_cast<SIZE_T>(size.QuadPart));
    if (!mem) {
        CloseHandle(file);
        return nullptr;
    }
    void* ptr = GlobalLock(mem);
    DWORD read = 0;
    const BOOL ok = ptr && ReadFile(file, ptr, static_cast<DWORD>(size.QuadPart), &read, nullptr);
    if (ptr) GlobalUnlock(mem);
    CloseHandle(file);
    if (!ok || static_cast<LONGLONG>(read) != size.QuadPart) {
        GlobalFree(mem);
        return nullptr;
    }

    IStream* stream = nullptr;
    if (FAILED(CreateStreamOnHGlobal(mem, TRUE, &stream))) {
        GlobalFree(mem);
        return nullptr;
    }

    Bitmap* source = Bitmap::FromStream(stream);
    Bitmap* result = nullptr;
    if (source && source->GetLastStatus() == Ok) {
        result = source->Clone(0, 0, source->GetWidth(), source->GetHeight(), PixelFormat32bppARGB);
        if (result && result->GetLastStatus() != Ok) {
            delete result;
            result = nullptr;
        }
    }
    delete source;
    stream->Release();
    return result;
}

bool InitDesktopWallpaper() {
    if (g_desktopWallpaper) return true;
    const HRESULT hr = CoCreateInstance(CLSID_DesktopWallpaper, nullptr, CLSCTX_ALL,
                                        IID_PPV_ARGS(&g_desktopWallpaper));
    if (FAILED(hr)) {
        g_desktopWallpaper = nullptr;
        return false;
    }
    return true;
}

bool QueryWallpaperPlacement(const RECT& widgetRect, WallpaperPlacement& out) {
    if (!InitDesktopWallpaper()) return false;

    UINT count = 0;
    if (FAILED(g_desktopWallpaper->GetMonitorDevicePathCount(&count))) {
        SafeRelease(g_desktopWallpaper);
        return false;
    }

    std::vector<MonitorInfo> monitors;
    for (UINT i = 0; i < count; ++i) {
        LPWSTR id = nullptr;
        if (SUCCEEDED(g_desktopWallpaper->GetMonitorDevicePathAt(i, &id)) && id) {
            MonitorInfo mi;
            mi.id = id;
            CoTaskMemFree(id);
            if (SUCCEEDED(g_desktopWallpaper->GetMonitorRECT(mi.id.c_str(), &mi.rc))) {
                monitors.push_back(mi);
            }
        }
    }
    if (monitors.empty()) return false;

    const POINT center = {(widgetRect.left + widgetRect.right) / 2,
                          (widgetRect.top + widgetRect.bottom) / 2};
    const MonitorInfo* chosen = &monitors[0];
    for (const MonitorInfo& m : monitors) {
        if (PtInRect(&m.rc, center)) {
            chosen = &m;
            break;
        }
    }

    DESKTOP_WALLPAPER_POSITION pos = DWPOS_FILL;
    if (FAILED(g_desktopWallpaper->GetPosition(&pos))) return false;

    COLORREF bg = 0;
    g_desktopWallpaper->GetBackgroundColor(&bg);

    out.position = static_cast<DWORD>(pos);
    out.background = bg;

    if (out.position == kPosSpan) {
        RECT virtualRect = monitors[0].rc;
        for (const MonitorInfo& m : monitors) UnionRect(&virtualRect, &virtualRect, &m.rc);
        out.rect = virtualRect;
    } else {
        out.rect = chosen->rc;
    }

    out.path.clear();
    LPWSTR wp = nullptr;
    if (SUCCEEDED(g_desktopWallpaper->GetWallpaper(chosen->id.c_str(), &wp)) && wp) {
        out.path = wp;
        CoTaskMemFree(wp);
    }
    return true;
}

void QueryRegistryPlacement(WallpaperPlacement& out) {
    out.path = ExpandEnv(ReadRegString(kDesktopKey, L"Wallpaper"));

    const std::wstring styleText = ReadRegString(kDesktopKey, L"WallpaperStyle");
    const std::wstring tileText = ReadRegString(kDesktopKey, L"TileWallpaper");
    const DWORD style = styleText.empty() ? 10u : static_cast<DWORD>(_wtoi(styleText.c_str()));
    const bool tile = tileText == L"1";

    if (style == 0 && tile) out.position = kPosTile;
    else if (style == 0) out.position = kPosCenter;
    else if (style == 2) out.position = kPosStretch;
    else if (style == 6) out.position = kPosFit;
    else if (style == 22) out.position = kPosSpan;
    else out.position = kPosFill;

    int r = 0, g = 0, b = 0;
    if (swscanf_s(ReadRegString(kColorsKey, L"Background").c_str(), L"%d %d %d", &r, &g, &b) != 3) {
        r = g = b = 0;
    }
    out.background = RGB(std::clamp(r, 0, 255), std::clamp(g, 0, 255), std::clamp(b, 0, 255));
    out.rect = RECT{0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)};
}

bool UpdateWallpaper(const RECT& widgetRect, bool force) {
    WallpaperPlacement next;
    const bool fromWindows = QueryWallpaperPlacement(widgetRect, next);
    if (!fromWindows) QueryRegistryPlacement(next);

    const std::wstring stamp = FileStamp(next.path);
    next.signature = next.path + L"|" + stamp + L"|" + std::to_wstring(next.position) + L"|" +
                     std::to_wstring(next.background) + L"|" +
                     std::to_wstring(next.rect.left) + L"," + std::to_wstring(next.rect.top) + L"," +
                     std::to_wstring(next.rect.right) + L"," + std::to_wstring(next.rect.bottom);

    if (!force && next.signature == g_wpPlacement.signature) return false;

    const std::wstring imageKey = next.path + L"|" + stamp;
    if (imageKey != g_wpImageKey) {
        Bitmap* img = nullptr;
        if (!next.path.empty()) {
            img = LoadWallpaperFile(next.path);
            if (!img) {
                wchar_t appData[MAX_PATH] = {};
                if (GetEnvironmentVariableW(L"APPDATA", appData, ARRAYSIZE(appData)) > 0) {
                    const std::wstring transcoded =
                        std::wstring(appData) + L"\\Microsoft\\Windows\\Themes\\TranscodedWallpaper";
                    img = LoadWallpaperFile(transcoded);
                }
            }
        }
        delete g_wpImage;
        g_wpImage = img;
        g_wpImageKey = imageKey;
    }

    g_wpPlacement = next;

    Wh_Log(L"Wallpaper source=%s (%s) image=%ux%u position=%u rect=(%ld,%ld)-(%ld,%ld) background=0x%06X",
           next.path.c_str(), fromWindows ? L"IDesktopWallpaper" : L"registry fallback",
           g_wpImage ? g_wpImage->GetWidth() : 0u, g_wpImage ? g_wpImage->GetHeight() : 0u,
           next.position, next.rect.left, next.rect.top, next.rect.right, next.rect.bottom,
           static_cast<unsigned>(next.background));
    return true;
}

void BuildWallpaperCrop(int cropX, int cropY, int cropW, int cropH, std::vector<uint32_t>& out) {
    const COLORREF bgRef = g_wpPlacement.background;
    Bitmap crop(cropW, cropH, cropW * 4, PixelFormat32bppARGB, reinterpret_cast<BYTE*>(out.data()));
    Graphics gc(&crop);
    gc.SetInterpolationMode(InterpolationModeHighQualityBicubic);
    gc.SetPixelOffsetMode(PixelOffsetModeHighQuality);
    gc.Clear(Color(255, GetRValue(bgRef), GetGValue(bgRef), GetBValue(bgRef)));

    if (!g_wpImage) return;

    const REAL imgW = static_cast<REAL>(g_wpImage->GetWidth());
    const REAL imgH = static_cast<REAL>(g_wpImage->GetHeight());
    if (imgW <= 0 || imgH <= 0) return;

    const RECT pr = g_wpPlacement.rect;
    const REAL ox = static_cast<REAL>(pr.left);
    const REAL oy = static_cast<REAL>(pr.top);
    const REAL pw = static_cast<REAL>(pr.right - pr.left);
    const REAL ph = static_cast<REAL>(pr.bottom - pr.top);
    if (pw <= 0 || ph <= 0) return;

    auto draw = [&](REAL x, REAL y, REAL w, REAL h) {
        gc.DrawImage(g_wpImage, RectF(x - static_cast<REAL>(cropX), y - static_cast<REAL>(cropY), w, h));
    };

    switch (g_wpPlacement.position) {
        case kPosTile: {
            const REAL startX = ox + std::floor((static_cast<REAL>(cropX) - ox) / imgW) * imgW;
            const REAL startY = oy + std::floor((static_cast<REAL>(cropY) - oy) / imgH) * imgH;
            const REAL endX = static_cast<REAL>(cropX + cropW);
            const REAL endY = static_cast<REAL>(cropY + cropH);
            for (REAL y = startY; y < endY; y += imgH) {
                for (REAL x = startX; x < endX; x += imgW) {
                    draw(x, y, imgW, imgH);
                }
            }
            break;
        }
        case kPosCenter:
            draw(ox + (pw - imgW) / 2.0f, oy + (ph - imgH) / 2.0f, imgW, imgH);
            break;
        case kPosStretch:
        case kPosSpan:
            draw(ox, oy, pw, ph);
            break;
        case kPosFit: {
            const REAL sc = std::min(pw / imgW, ph / imgH);
            const REAL w = imgW * sc;
            const REAL h = imgH * sc;
            draw(ox + (pw - w) / 2.0f, oy + (ph - h) / 2.0f, w, h);
            break;
        }
        case kPosFill:
        default: {
            const REAL sc = std::max(pw / imgW, ph / imgH);
            const REAL w = imgW * sc;
            const REAL h = imgH * sc;
            draw(ox + (pw - w) / 2.0f, oy + (ph - h) / 2.0f, w, h);
            break;
        }
    }
}

bool UpdateCrop(SlotBuffers& buf, int cropX, int cropY, int cropW, int cropH) {
    if (buf.crop.size() != static_cast<size_t>(cropW) * cropH) {
        buf.crop.assign(static_cast<size_t>(cropW) * cropH, 0u);
    }
    const std::wstring key = std::to_wstring(cropX) + L"," + std::to_wstring(cropY) + L"," +
                             std::to_wstring(cropW) + L"," + std::to_wstring(cropH) + L"|" +
                             g_wpPlacement.signature;
    if (key != buf.cropKey) {
        BuildWallpaperCrop(cropX, cropY, cropW, cropH, buf.crop);
        buf.cropKey = key;
        return true;
    }
    return false;
}

// ── GPU glass (Direct3D 11) ──

constexpr char kGlassHlsl[] = R"HLSL(
cbuffer GlassParams : register(b0)
{
    float2 gSize;
    float2 gCrop;
    float  gMargin;
    float  gRadius;
    float  gEdgeWidth;
    float  gRefract;
    float  gBlur;
    float  gChroma;
    float  gSpec;
    float  gSheen;
    float  gRim;
    float  gGrain;
    float  gScale;
    float  gShadow;
    float2 gOrigin;
    float2 gPad1;
    float4 gTintTop;
    float4 gTintBottom;
    float  gSheenWidth;
    float  gPhase;
    float2 gPad2;
};

Texture2D gWall : register(t0);
SamplerState gSamp : register(s0);

struct VSOut
{
    float4 pos : SV_Position;
};

VSOut VSMain(uint id : SV_VertexID)
{
    VSOut o;
    float2 uv = float2((id << 1) & 2, id & 2);
    o.pos = float4(uv * float2(2.0, -2.0) + float2(-1.0, 1.0), 0.0, 1.0);
    return o;
}

float Sdf(float2 p)
{
    float2 center = gOrigin + gSize * 0.5;
    float2 halfSize = gSize * 0.5;
    float2 q = abs(p - center) - (halfSize - gRadius);
    return length(max(q, 0.0)) + min(max(q.x, q.y), 0.0) - gRadius;
}

float Hash(float2 p)
{
    return frac(sin(dot(p, float2(127.1, 311.7))) * 43758.5453);
}

float ValueNoise(float2 p)
{
    float2 i = floor(p);
    float2 f = frac(p);
    float2 u = f * f * (3.0 - 2.0 * f);
    float a = Hash(i);
    float b = Hash(i + float2(1.0, 0.0));
    float c = Hash(i + float2(0.0, 1.0));
    float d = Hash(i + float2(1.0, 1.0));
    return lerp(lerp(a, b, u.x), lerp(c, d, u.x), u.y);
}

float3 BlurSample(float2 cp)
{
    float3 acc = float3(0.0, 0.0, 0.0);
    [unroll]
    for (int i = 0; i < 16; i++)
    {
        float fi = (float)i;
        float ang = fi * 2.39996323;
        float r = sqrt((fi + 0.5) / 16.0) * gBlur;
        float2 off = float2(cos(ang), sin(ang)) * r;
        acc += gWall.SampleLevel(gSamp, (cp + off) / gCrop, 0).rgb;
    }
    return acc / 16.0;
}

float4 PSMain(float4 pos : SV_Position) : SV_Target
{
    float2 p = pos.xy;

    float sdf = Sdf(p);
    float inside = saturate(0.5 - sdf);
    float shadowSdf = Sdf(p - float2(0.0, 3.0 * gScale));
    float shadowA = (1.0 - smoothstep(0.0, 8.0 * gScale, shadowSdf)) * gShadow * (1.0 - inside);

    float depth = saturate(-sdf / gEdgeWidth);
    float bevel = sqrt(saturate(1.0 - (1.0 - depth) * (1.0 - depth)));
    float edge = 1.0 - bevel;

    float2 gx = float2(Sdf(p + float2(1.0, 0.0)) - Sdf(p - float2(1.0, 0.0)),
                       Sdf(p + float2(0.0, 1.0)) - Sdf(p - float2(0.0, 1.0))) * 0.5;
    float2 nOut = gx / max(length(gx), 1e-4);

    float3 N = normalize(float3(nOut * edge * 1.6, 1.0));

    float2 wobP = p * 0.045;
    float2 wob = float2(ValueNoise(wobP + 3.1), ValueNoise(wobP + 17.7)) - 0.5;
    float2 disp = -nOut * gRefract * edge * edge + wob * gRefract * 0.30;
    float2 basePos = p + gMargin + disp;
    float2 caOff = nOut * gChroma * gRefract * edge;

    float3 col;
    col.r = BlurSample(basePos + caOff).r;
    col.g = BlurSample(basePos).g;
    col.b = BlurSample(basePos - caOff).b;

    float vy = saturate((p.y - gOrigin.y) / gSize.y);
    float4 tint = lerp(gTintTop, gTintBottom, vy);
    float3 glass = lerp(col, tint.rgb, tint.a);
    glass *= lerp(0.78, 1.0, bevel);

    float3 L = normalize(float3(-0.45, -0.75, 0.55));
    float3 H = normalize(L + float3(0.0, 0.0, 1.0));
    float ndh = saturate(dot(N, H));
    float specular = pow(ndh, 42.0) * gSpec * edge * edge;
    float broad = pow(ndh, 6.0) * 0.10;

    float2 gp = (p - gOrigin) / gSize;
    float bandCenter = gPhase < 0.0 ? 0.55 : lerp(-0.6, 1.6, gPhase);
    float bandX = gp.x * 0.7 + gp.y * 0.6 - bandCenter;
    float band = exp(-(bandX * bandX) / max(gSheenWidth, 0.001)) * gSheen;
    float topWash = (1.0 - smoothstep(0.0, 0.55, gp.y)) * gSheen * 0.6;

    float lit = saturate(dot(nOut, float2(-0.6, -0.8)) * 0.5 + 0.5);
    float rimLine = saturate(1.0 - abs(sdf + 0.8) / 1.2) * gRim * lerp(0.4, 1.0, lit);

    float grain = (Hash(floor(p)) - 0.5) * gGrain;
    float frost = (ValueNoise(p * 0.35) - 0.5) * gGrain * 0.6;

    float3 outc = glass;
    outc += specular + broad;
    outc += band + topWash;
    outc += rimLine;
    outc += grain + frost;
    outc = saturate(outc);

    return float4(outc * inside, inside + shadowA);
}
)HLSL";

void ReleaseTargets(GpuTargets& t) {
    SafeRelease(t.staging);
    SafeRelease(t.rtv);
    SafeRelease(t.rtTex);
    SafeRelease(t.cropSrv);
    SafeRelease(t.cropTex);
    t.outW = t.outH = t.cropW = t.cropH = 0;
}

void ReleaseGpu() {
    for (GpuTargets& t : g_gpu.targets) ReleaseTargets(t);
    if (g_gpu.ctx) g_gpu.ctx->ClearState();
    SafeRelease(g_gpu.rasterState);
    SafeRelease(g_gpu.sampler);
    SafeRelease(g_gpu.cb);
    SafeRelease(g_gpu.ps);
    SafeRelease(g_gpu.vs);
    SafeRelease(g_gpu.ctx);
    SafeRelease(g_gpu.device);
    g_gpu.ready = false;
}

bool InitGpu() {
    if (g_gpu.ready) return true;

    const D3D_FEATURE_LEVEL levels[] = {D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0};
    const D3D_DRIVER_TYPE drivers[] = {D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP};

    HRESULT hr = E_FAIL;
    for (D3D_DRIVER_TYPE driver : drivers) {
        hr = D3D11CreateDevice(nullptr, driver, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT,
                               levels, ARRAYSIZE(levels), D3D11_SDK_VERSION,
                               &g_gpu.device, nullptr, &g_gpu.ctx);
        if (SUCCEEDED(hr)) break;
    }
    if (FAILED(hr) || !g_gpu.device || !g_gpu.ctx) {
        Wh_Log(L"Direct3D 11 device creation failed (0x%08X); using CPU glass", static_cast<unsigned>(hr));
        ReleaseGpu();
        return false;
    }

    ID3DBlob* vsBlob = nullptr;
    ID3DBlob* psBlob = nullptr;
    ID3DBlob* errBlob = nullptr;
    const size_t srcLen = std::strlen(kGlassHlsl);

    hr = D3DCompile(kGlassHlsl, srcLen, "lvt-glass.hlsl", nullptr, nullptr, "VSMain", "vs_5_0",
                    D3DCOMPILE_OPTIMIZATION_LEVEL3, 0, &vsBlob, &errBlob);
    if (FAILED(hr)) {
        if (errBlob) Wh_Log(L"Vertex shader compile error: %S", static_cast<const char*>(errBlob->GetBufferPointer()));
        SafeRelease(errBlob);
        ReleaseGpu();
        return false;
    }
    SafeRelease(errBlob);

    hr = D3DCompile(kGlassHlsl, srcLen, "lvt-glass.hlsl", nullptr, nullptr, "PSMain", "ps_5_0",
                    D3DCOMPILE_OPTIMIZATION_LEVEL3, 0, &psBlob, &errBlob);
    if (FAILED(hr)) {
        if (errBlob) Wh_Log(L"Pixel shader compile error: %S", static_cast<const char*>(errBlob->GetBufferPointer()));
        SafeRelease(errBlob);
        SafeRelease(vsBlob);
        ReleaseGpu();
        return false;
    }
    SafeRelease(errBlob);

    hr = g_gpu.device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(),
                                          nullptr, &g_gpu.vs);
    if (SUCCEEDED(hr)) {
        hr = g_gpu.device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(),
                                             nullptr, &g_gpu.ps);
    }
    SafeRelease(vsBlob);
    SafeRelease(psBlob);
    if (FAILED(hr)) {
        ReleaseGpu();
        return false;
    }

    D3D11_BUFFER_DESC bd = {};
    bd.ByteWidth = sizeof(GlassCB);
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    hr = g_gpu.device->CreateBuffer(&bd, nullptr, &g_gpu.cb);

    D3D11_SAMPLER_DESC sd = {};
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sd.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    sd.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sd.MaxLOD = D3D11_FLOAT32_MAX;
    if (SUCCEEDED(hr)) hr = g_gpu.device->CreateSamplerState(&sd, &g_gpu.sampler);

    D3D11_RASTERIZER_DESC rd = {};
    rd.FillMode = D3D11_FILL_SOLID;
    rd.CullMode = D3D11_CULL_NONE;
    rd.DepthClipEnable = TRUE;
    if (SUCCEEDED(hr)) hr = g_gpu.device->CreateRasterizerState(&rd, &g_gpu.rasterState);

    if (FAILED(hr)) {
        Wh_Log(L"Direct3D 11 resource creation failed (0x%08X); using CPU glass", static_cast<unsigned>(hr));
        ReleaseGpu();
        return false;
    }

    g_gpu.ready = true;
    return true;
}

bool EnsureTargets(GpuTargets& t, int outW, int outH, int cropW, int cropH) {
    if (!g_gpu.device) return false;
    if (t.rtTex && t.outW == outW && t.outH == outH && t.cropW == cropW && t.cropH == cropH) {
        return true;
    }
    ReleaseTargets(t);

    D3D11_TEXTURE2D_DESC td = {};
    td.Width = static_cast<UINT>(outW);
    td.Height = static_cast<UINT>(outH);
    td.MipLevels = 1;
    td.ArraySize = 1;
    td.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    td.SampleDesc.Count = 1;
    td.Usage = D3D11_USAGE_DEFAULT;
    td.BindFlags = D3D11_BIND_RENDER_TARGET;
    if (FAILED(g_gpu.device->CreateTexture2D(&td, nullptr, &t.rtTex))) return false;
    if (FAILED(g_gpu.device->CreateRenderTargetView(t.rtTex, nullptr, &t.rtv))) return false;

    td.Usage = D3D11_USAGE_STAGING;
    td.BindFlags = 0;
    td.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    if (FAILED(g_gpu.device->CreateTexture2D(&td, nullptr, &t.staging))) return false;

    td.Width = static_cast<UINT>(cropW);
    td.Height = static_cast<UINT>(cropH);
    td.Usage = D3D11_USAGE_DEFAULT;
    td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    td.CPUAccessFlags = 0;
    if (FAILED(g_gpu.device->CreateTexture2D(&td, nullptr, &t.cropTex))) return false;
    if (FAILED(g_gpu.device->CreateShaderResourceView(t.cropTex, nullptr, &t.cropSrv))) return false;

    t.outW = outW;
    t.outH = outH;
    t.cropW = cropW;
    t.cropH = cropH;
    return true;
}

bool GpuRenderGlass(GpuTargets& t, const GlassCB& cb, const std::vector<uint32_t>& crop,
                    int cropW, int cropH, std::vector<uint32_t>& out, int outW, int outH) {
    if (!g_gpu.ready) return false;
    if (!EnsureTargets(t, outW, outH, cropW, cropH)) return false;

    ID3D11DeviceContext* ctx = g_gpu.ctx;
    ctx->UpdateSubresource(t.cropTex, 0, nullptr, crop.data(), static_cast<UINT>(cropW * 4), 0);
    ctx->UpdateSubresource(g_gpu.cb, 0, nullptr, &cb, 0, 0);

    ID3D11RenderTargetView* rtv = t.rtv;
    ctx->OMSetRenderTargets(1, &rtv, nullptr);
    const float clearColor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    ctx->ClearRenderTargetView(rtv, clearColor);

    D3D11_VIEWPORT vp = {};
    vp.Width = static_cast<float>(outW);
    vp.Height = static_cast<float>(outH);
    vp.MaxDepth = 1.0f;
    ctx->RSSetViewports(1, &vp);
    ctx->RSSetState(g_gpu.rasterState);
    ctx->IASetInputLayout(nullptr);
    ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    ctx->VSSetShader(g_gpu.vs, nullptr, 0);
    ctx->PSSetShader(g_gpu.ps, nullptr, 0);

    ID3D11Buffer* cbuf = g_gpu.cb;
    ctx->PSSetConstantBuffers(0, 1, &cbuf);
    ID3D11ShaderResourceView* srv = t.cropSrv;
    ctx->PSSetShaderResources(0, 1, &srv);
    ID3D11SamplerState* samp = g_gpu.sampler;
    ctx->PSSetSamplers(0, 1, &samp);

    ctx->Draw(3, 0);

    ID3D11ShaderResourceView* nullSrv = nullptr;
    ctx->PSSetShaderResources(0, 1, &nullSrv);
    ID3D11RenderTargetView* nullRtv = nullptr;
    ctx->OMSetRenderTargets(1, &nullRtv, nullptr);

    ctx->CopyResource(t.staging, t.rtTex);
    D3D11_MAPPED_SUBRESOURCE mapped = {};
    if (FAILED(ctx->Map(t.staging, 0, D3D11_MAP_READ, 0, &mapped))) return false;

    const uint8_t* src = static_cast<const uint8_t*>(mapped.pData);
    uint8_t* dst = reinterpret_cast<uint8_t*>(out.data());
    for (int y = 0; y < outH; ++y) {
        std::memcpy(dst + static_cast<size_t>(y) * outW * 4,
                    src + static_cast<size_t>(y) * mapped.RowPitch,
                    static_cast<size_t>(outW) * 4);
    }
    ctx->Unmap(t.staging, 0);
    return true;
}

float SheenPhase(const WeatherConfig& cfg) {
    if (!cfg.glass.animate || !cfg.useGpu || !g_gpu.ready) return -1.0f;
    const ULONGLONG periodMs = static_cast<ULONGLONG>(cfg.glass.periodSec) * 1000ULL;
    return static_cast<float>(GetTickCount64() % periodMs) / static_cast<float>(periodMs);
}

GlassCB MakeGlassParams(const GlassSettings& gs, float s, float phase,
                        int glassW, int glassH, int pad, int margin, int cropW, int cropH) {
    GlassCB cb = {};
    cb.size[0] = static_cast<float>(glassW);
    cb.size[1] = static_cast<float>(glassH);
    cb.crop[0] = static_cast<float>(cropW);
    cb.crop[1] = static_cast<float>(cropH);
    cb.margin = static_cast<float>(margin);
    cb.radius = kCornerRadius * s;
    cb.edgeWidth = static_cast<float>(gs.bevelPx) * s;
    cb.refract = static_cast<float>(gs.refractionPx) * s;
    cb.blur = static_cast<float>(gs.blurPx) * s;
    cb.chroma = gs.chromaPct / 100.0f;
    cb.spec = gs.specularPct / 100.0f;
    cb.sheen = gs.sheenPct / 100.0f;
    cb.sheenWidth = gs.sheenWidthPct / 1000.0f;
    cb.rim = gs.rimPct / 100.0f;
    cb.grain = gs.grainPct / 1000.0f;
    cb.scale = s;
    cb.shadow = gs.shadowPct / 100.0f;
    cb.phase = phase;
    cb.origin[0] = static_cast<float>(pad);
    cb.origin[1] = static_cast<float>(pad);
    cb.tintTop[0] = GetRValue(gs.tintTop) / 255.0f;
    cb.tintTop[1] = GetGValue(gs.tintTop) / 255.0f;
    cb.tintTop[2] = GetBValue(gs.tintTop) / 255.0f;
    cb.tintTop[3] = gs.tintTopOpacityPct / 100.0f;
    cb.tintBottom[0] = GetRValue(gs.tintBottom) / 255.0f;
    cb.tintBottom[1] = GetGValue(gs.tintBottom) / 255.0f;
    cb.tintBottom[2] = GetBValue(gs.tintBottom) / 255.0f;
    cb.tintBottom[3] = gs.tintBottomOpacityPct / 100.0f;
    return cb;
}

bool ShouldUseDarkText(const std::vector<uint32_t>& px, int bufW, int pad, int glassW, int glassH) {
    double sum = 0.0;
    int count = 0;
    for (int y = pad; y < pad + glassH; y += 3) {
        for (int x = pad; x < pad + glassW; x += 3) {
            const uint32_t c = px[static_cast<size_t>(y) * bufW + x];
            const double b = c & 0xFF;
            const double g = (c >> 8) & 0xFF;
            const double r = (c >> 16) & 0xFF;
            sum += 0.299 * r + 0.587 * g + 0.114 * b;
            ++count;
        }
    }
    return count > 0 && (sum / count) > 170.0;
}

// ── Calendar drawing ──

Ink MakeInk(bool glass, bool darkText) {
    Ink k;
    if (!glass) {
        k.text = Color(245, 255, 255, 255);
        k.soft = Color(170, 255, 255, 255);
        k.dim = Color(110, 255, 255, 255);
        k.title = Color(255, 255, 59, 48);
        k.today = Color(255, 255, 59, 48);
        k.todayText = Color(245, 255, 255, 255);
        k.rowFill = Color(255, 46, 46, 50);
    } else if (darkText) {
        k.text = Color(245, 22, 26, 34);
        k.soft = Color(190, 22, 26, 34);
        k.dim = Color(120, 22, 26, 34);
        k.title = Color(245, 22, 26, 34);
        k.today = Color(245, 22, 26, 34);
        k.todayText = Color(245, 255, 255, 255);
        k.rowFill = Color(46, 22, 26, 34);
    } else {
        k.text = Color(245, 255, 255, 255);
        k.soft = Color(170, 255, 255, 255);
        k.dim = Color(110, 255, 255, 255);
        k.title = Color(245, 255, 255, 255);
        k.today = Color(245, 255, 255, 255);
        k.todayText = Color(255, 25, 25, 30);
        k.rowFill = Color(46, 255, 255, 255);
    }
    return k;
}

std::wstring FormatMinute(int minute) {
    wchar_t buf[16];
    const int h = minute / 60;
    const int m = minute % 60;
    const int h12 = h % 12 == 0 ? 12 : h % 12;
    swprintf_s(buf, L"%d:%02d %ls", h12, m, h < 12 ? L"AM" : L"PM");
    return buf;
}

void DrawStatusNote(Graphics& g, FontFamily& sans, float x, float y, float w,
                    FetchStatus status, Color color) {
    if (status == FetchStatus::NoUrl) {
        DrawLabel(g, L"Set URL", sans, 8, FontStyleRegular, RectF(x, y, w, 16.0f),
                  StringAlignmentFar, StringAlignmentCenter, color);
    } else if (status == FetchStatus::Failed) {
        DrawLabel(g, L"Offline", sans, 8, FontStyleRegular, RectF(x, y, w, 16.0f),
                  StringAlignmentFar, StringAlignmentCenter, color);
    }
}

void DrawMonthGrid(Graphics& g, float ox, float oy, float gridX, float gridW,
                   const SYSTEMTIME& today, const std::vector<bool>& marks,
                   bool showDots, const Ink& ink, FetchStatus status) {
    FontFamily sans(L"Segoe UI");
    const float colW = gridW / 7.0f;
    const float x0 = ox + gridX;

    // The full month name gets the row, leaving room at the right only when a status note shows.
    const float noteW = status == FetchStatus::Ok ? 0.0f : 40.0f;
    DrawLabel(g, kMonthNames[today.wMonth - 1], sans, 10, FontStyleBold,
              RectF(x0, oy + kTitleY, gridW - noteW, 16.0f),
              StringAlignmentNear, StringAlignmentCenter, ink.title);
    if (noteW > 0.0f) {
        DrawStatusNote(g, sans, x0 + gridW - noteW, oy + kTitleY, noteW, status, ink.soft);
    }

    static const wchar_t* const kWeekdays[7] = {L"S", L"M", L"T", L"W", L"T", L"F", L"S"};
    for (int i = 0; i < 7; ++i) {
        const Color c = (i == 0 || i == 6) ? ink.dim : ink.soft;
        DrawLabel(g, kWeekdays[i], sans, 9, FontStyleBold,
                  RectF(x0 + i * colW, oy + kWeekdayY, colW, 12.0f),
                  StringAlignmentCenter, StringAlignmentCenter, c);
    }

    const int firstWeekday = Weekday(DaysFromCivil(today.wYear, today.wMonth, 1));
    const int dim = static_cast<int>(marks.size());
    for (int day = 1; day <= dim; ++day) {
        const int index = firstWeekday + day - 1;
        const int row = index / 7;
        const int col = index % 7;
        const float cellX = x0 + col * colW;
        const float rowTop = oy + kGridY + row * kRowH;
        const float cx = cellX + colW / 2.0f;
        const float cy = rowTop + kRowH / 2.0f;
        const bool isToday = day == today.wDay;
        const bool weekend = col == 0 || col == 6;

        if (isToday) {
            SolidBrush fill(ink.today);
            FillEllipseF(g, &fill, cx - kCircleD / 2.0f, cy - kCircleD / 2.0f, kCircleD, kCircleD);
        }

        wchar_t label[4];
        swprintf_s(label, L"%d", day);
        const Color textColor = isToday ? ink.todayText : (weekend ? ink.dim : ink.text);
        DrawLabel(g, label, sans, 9, isToday ? FontStyleBold : FontStyleRegular,
                  RectF(cellX, rowTop, colW, kRowH),
                  StringAlignmentCenter, StringAlignmentCenter, textColor);

        if (showDots && !isToday && marks[static_cast<size_t>(day - 1)]) {
            SolidBrush dot(ink.soft);
            FillEllipseF(g, &dot, cx - 1.5f, rowTop + kRowH - 3.0f, 3.0f, 3.0f);
        }
    }
}

void DrawUpcomingList(Graphics& g, float ox, float oy, const std::vector<UpcomingItem>& items,
                      const Ink& ink, FetchStatus status) {
    FontFamily sans(L"Segoe UI");
    const Color bar(255, 94, 206, 214);

    DrawLabel(g, L"Upcoming", sans, 9, FontStyleRegular,
              RectF(ox + kPadX, oy + kTitleY, kUpcomingListW, 16.0f),
              StringAlignmentNear, StringAlignmentCenter, ink.soft);

    if (status != FetchStatus::Ok) {
        DrawStatusNote(g, sans, ox + kPadX, oy + kWeekdayY, kUpcomingListW, status, ink.soft);
        return;
    }
    if (items.empty()) {
        DrawLabel(g, L"No upcoming events", sans, 8, FontStyleRegular,
                  RectF(ox + kPadX, oy + kWeekdayY, kUpcomingListW, 16.0f),
                  StringAlignmentNear, StringAlignmentCenter, ink.soft);
        return;
    }

    for (size_t i = 0; i < items.size() && i < kUpcomingRows; ++i) {
        const UpcomingItem& item = items[i];
        const float rowY = oy + kWeekdayY + 2.0f + static_cast<float>(i) * 34.0f;
        const RectF row(ox + kPadX, rowY, kUpcomingListW, 30.0f);
        DrawRoundedRectangle(g, row, 7.0f, SolidBrush(ink.rowFill));
        DrawRoundedRectangle(g, RectF(row.X + 4.0f, row.Y + 6.0f, 2.5f, 18.0f), 1.25f, SolidBrush(bar));

        DrawLabel(g, item.title.c_str(), sans, 8, FontStyleBold,
                  RectF(row.X + 11.0f, row.Y, kUpcomingListW - 11.0f - 42.0f, 30.0f),
                  StringAlignmentNear, StringAlignmentCenter, ink.text);

        const Ymd ymd = CivilFromDays(item.day);
        wchar_t date[16];
        swprintf_s(date, L"%ls %d", kMonthAbbrev[ymd.m - 1], ymd.d);
        DrawLabel(g, date, sans, 7, FontStyleRegular,
                  RectF(row.X + kUpcomingListW - 40.0f, row.Y, 36.0f, 30.0f),
                  StringAlignmentFar, StringAlignmentCenter, ink.soft);
    }
}

void DrawAgendaList(Graphics& g, float ox, float oy,
                    const std::vector<std::vector<AgendaItem>>& days, int64_t fromDay,
                    const SYSTEMTIME& today, const Ink& ink, FetchStatus status) {
    FontFamily sans(L"Segoe UI");

    DrawLabel(g, L"THIS WEEK", sans, 10, FontStyleBold,
              RectF(ox + kPadX, oy + kTitleY, 150.0f, 16.0f),
              StringAlignmentNear, StringAlignmentCenter, ink.title);
    DrawStatusNote(g, sans, ox + kAgendaW - kPadX - 80.0f, oy + kTitleY, 80.0f, status, ink.soft);

    const float labelW = 56.0f;
    const float eventX = ox + kPadX + labelW + 8.0f;
    const float eventW = kAgendaW - kPadX - labelW - 8.0f - kPadX;
    const int todayIndex = static_cast<int>(DaysFromCivil(today.wYear, today.wMonth, today.wDay) - fromDay);

    for (size_t i = 0; i < days.size(); ++i) {
        const float rowY = oy + kAgendaTop + static_cast<float>(i) * kAgendaRowH;
        const int64_t day = fromDay + static_cast<int64_t>(i);
        const Ymd ymd = CivilFromDays(day);
        const bool isToday = static_cast<int>(i) == todayIndex;

        wchar_t label[24];
        swprintf_s(label, L"%ls %d", kDayAbbrev[Weekday(day)], ymd.d);
        DrawLabel(g, label, sans, 9, FontStyleBold,
                  RectF(ox + kPadX, rowY, labelW, kAgendaRowH),
                  StringAlignmentNear, StringAlignmentCenter, isToday ? ink.title : ink.text);

        const std::vector<AgendaItem>& items = days[i];
        if (items.empty()) {
            DrawLabel(g, L"No events", sans, 8, FontStyleRegular,
                      RectF(eventX, rowY, eventW, kAgendaRowH),
                      StringAlignmentNear, StringAlignmentCenter, ink.dim);
        } else {
            const bool more = items.size() > 2;
            const size_t lines = more ? 2 : items.size();
            for (size_t j = 0; j < lines; ++j) {
                const float lineY = rowY + 3.0f + static_cast<float>(j) * 14.0f;
                if (more && j == 1) {
                    wchar_t extra[24];
                    swprintf_s(extra, L"+%u more", static_cast<unsigned>(items.size() - 1));
                    DrawLabel(g, extra, sans, 8, FontStyleRegular,
                              RectF(eventX, lineY, eventW, 13.0f),
                              StringAlignmentNear, StringAlignmentCenter, ink.soft);
                    break;
                }
                const AgendaItem& item = items[j];
                const std::wstring timeText = item.allDay ? L"All day" : FormatMinute(item.minute);
                DrawLabel(g, timeText.c_str(), sans, 7, FontStyleRegular,
                          RectF(eventX, lineY, 50.0f, 13.0f),
                          StringAlignmentNear, StringAlignmentCenter, ink.soft);
                DrawLabel(g, item.title.c_str(), sans, 8, FontStyleBold,
                          RectF(eventX + 52.0f, lineY, eventW - 52.0f, 13.0f),
                          StringAlignmentNear, StringAlignmentCenter, ink.text);
            }
        }

        if (i + 1 < days.size()) {
            Pen divider(Color(40, 255, 255, 255), 1.0f);
            g.DrawLine(&divider, ox + kPadX, rowY + kAgendaRowH - 1.0f,
                       ox + kAgendaW - kPadX, rowY + kAgendaRowH - 1.0f);
        }
    }
}

void DrawTodayPanel(Graphics& g, float ox, float oy, const std::vector<AgendaItem>& items,
                    const SYSTEMTIME& today, const Ink& ink, FetchStatus status) {
    FontFamily sans(L"Segoe UI");
    FontFamily light(L"Segoe UI Light");

    DrawLabel(g, kDayNames[Weekday(DaysFromCivil(today.wYear, today.wMonth, today.wDay))], sans, 9,
              FontStyleBold, RectF(ox + kPadX, oy + kTitleY, 110.0f, 14.0f),
              StringAlignmentNear, StringAlignmentCenter, ink.title);
    DrawStatusNote(g, sans, ox + kPadX, oy + kTitleY, kTodayW - 2.0f * kPadX, status, ink.soft);

    wchar_t dayNumber[4];
    swprintf_s(dayNumber, L"%d", today.wDay);
    DrawLabel(g, dayNumber, light, 40, FontStyleRegular,
              RectF(ox + kPadX - 2.0f, oy + 22.0f, 60.0f, 46.0f),
              StringAlignmentNear, StringAlignmentCenter, ink.text);
    DrawLabel(g, kMonthNames[today.wMonth - 1], sans, 9, FontStyleBold,
              RectF(ox + 66.0f, oy + 40.0f, 70.0f, 14.0f),
              StringAlignmentNear, StringAlignmentCenter, ink.soft);

    Pen divider(Color(60, 255, 255, 255), 1.0f);
    g.DrawLine(&divider, ox + kPadX, oy + 74.0f, ox + kTodayW - kPadX, oy + 74.0f);

    if (items.empty()) {
        DrawLabel(g, L"No events today", sans, 8, FontStyleRegular,
                  RectF(ox + kPadX, oy + 82.0f, kTodayW - 2.0f * kPadX, 14.0f),
                  StringAlignmentNear, StringAlignmentCenter, ink.soft);
        return;
    }

    const size_t maxLines = 4;
    const bool more = items.size() > maxLines;
    const size_t lines = more ? maxLines - 1 : items.size();
    for (size_t j = 0; j < lines; ++j) {
        const float lineY = oy + 82.0f + static_cast<float>(j) * 13.0f;
        const AgendaItem& item = items[j];
        const std::wstring timeText = item.allDay ? L"All day" : FormatMinute(item.minute);
        DrawLabel(g, timeText.c_str(), sans, 7, FontStyleRegular,
                  RectF(ox + kPadX, lineY, 42.0f, 13.0f),
                  StringAlignmentNear, StringAlignmentCenter, ink.soft);
        DrawLabel(g, item.title.c_str(), sans, 8, FontStyleBold,
                  RectF(ox + 56.0f, lineY, kTodayW - 56.0f - kPadX, 13.0f),
                  StringAlignmentNear, StringAlignmentCenter, ink.text);
    }
    if (more) {
        wchar_t extra[24];
        swprintf_s(extra, L"+%u more", static_cast<unsigned>(items.size() - lines));
        DrawLabel(g, extra, sans, 8, FontStyleRegular,
                  RectF(ox + kPadX, oy + 82.0f + static_cast<float>(lines) * 13.0f, kTodayW - 2.0f * kPadX, 13.0f),
                  StringAlignmentNear, StringAlignmentCenter, ink.soft);
    }
}

const std::vector<CalEvent>& EventsOf(const EventSnapshot& snap) {
    static const std::vector<CalEvent> kNoEvents;
    return snap.events ? *snap.events : kNoEvents;
}

const std::vector<bool>& MarksFor(int year, int month, const EventSnapshot& snap) {
    if (g_marks.year == year && g_marks.month == month && g_marks.version == snap.version) {
        return g_marks.days;
    }
    g_marks.year = year;
    g_marks.month = month;
    g_marks.version = snap.version;
    g_marks.days = BuildMonthMarks(EventsOf(snap), year, month);
    return g_marks.days;
}

// ── Clock drawing ──

ClockInk MakeClockInk(int style, bool darkText) {
    ClockInk k;
    if (style == kStyleDark) {
        k.face = Color(255, 40, 40, 44);
        k.ticks = Color(255, 235, 235, 240);
        k.hands = Color(255, 245, 245, 247);
        k.text = Color(245, 255, 255, 255);
        k.soft = Color(170, 255, 255, 255);
    } else if (style == kStyleLight) {
        k.face = Color(255, 255, 255, 255);
        k.ticks = Color(255, 40, 40, 44);
        k.hands = Color(255, 28, 28, 30);
        k.text = Color(255, 28, 28, 30);
        k.soft = Color(160, 28, 28, 30);
    } else if (darkText) {
        k.face = Color(70, 255, 255, 255);
        k.ticks = Color(235, 22, 26, 34);
        k.hands = Color(245, 22, 26, 34);
        k.text = Color(245, 22, 26, 34);
        k.soft = Color(190, 22, 26, 34);
    } else {
        k.face = Color(60, 255, 255, 255);
        k.ticks = Color(235, 255, 255, 255);
        k.hands = Color(245, 255, 255, 255);
        k.text = Color(245, 255, 255, 255);
        k.soft = Color(190, 255, 255, 255);
    }
    k.accent = Color(255, 255, 159, 10);
    return k;
}

void DrawHand(Graphics& g, float cx, float cy, float deg, float len, float tail, float width, Color color) {
    const float a = deg * kPiF / 180.0f;
    Pen pen(color, width);
    pen.SetStartCap(LineCapRound);
    pen.SetEndCap(LineCapRound);
    g.DrawLine(&pen, cx - tail * std::sin(a), cy + tail * std::cos(a),
               cx + len * std::sin(a), cy - len * std::cos(a));
}

// Draws a dial with minute and hour ticks, optional numbers, and hour, minute, and second hands.
void DrawAnalogFace(Graphics& g, float cx, float cy, float r, const ClockInk& k,
                    int hour, int minute, int second, bool numbers, bool secondHand) {
    SolidBrush face(k.face);
    FillEllipseF(g, &face, cx - r, cy - r, r * 2.0f, r * 2.0f);

    for (int i = 0; i < 60; ++i) {
        const bool major = i % 5 == 0;
        const float a = i * 6.0f * kPiF / 180.0f;
        const float outer = r * 0.94f;
        const float inner = major ? r * 0.80f : r * 0.88f;
        Pen pen(k.ticks, major ? r * 0.035f : r * 0.012f);
        g.DrawLine(&pen, cx + inner * std::sin(a), cy - inner * std::cos(a),
                   cx + outer * std::sin(a), cy - outer * std::cos(a));
    }

    if (numbers) {
        FontFamily sans(L"Segoe UI");
        for (int n = 1; n <= 12; ++n) {
            const float a = n * 30.0f * kPiF / 180.0f;
            const float x = cx + r * 0.66f * std::sin(a);
            const float y = cy - r * 0.66f * std::cos(a);
            wchar_t label[4];
            swprintf_s(label, L"%d", n);
            DrawLabel(g, label, sans, r * 0.22f, FontStyleRegular,
                      RectF(x - r * 0.25f, y - r * 0.16f, r * 0.5f, r * 0.32f),
                      StringAlignmentCenter, StringAlignmentCenter, k.text);
        }
    }

    const float hourDeg = (hour % 12 + minute / 60.0f) * 30.0f;
    const float minuteDeg = (minute + second / 60.0f) * 6.0f;
    const float secondDeg = second * 6.0f;
    DrawHand(g, cx, cy, hourDeg, r * 0.50f, 0.0f, r * 0.075f, k.hands);
    DrawHand(g, cx, cy, minuteDeg, r * 0.78f, r * 0.08f, r * 0.05f, k.hands);
    if (secondHand) {
        DrawHand(g, cx, cy, secondDeg, r * 0.86f, r * 0.22f, r * 0.02f, k.accent);
    }
    SolidBrush hub(k.accent);
    FillEllipseF(g, &hub, cx - r * 0.07f, cy - r * 0.07f, r * 0.14f, r * 0.14f);
}

// Tick marks around the edge of a rounded square, for the digital layouts. Each tick is placed
// at an even spacing along the perimeter and points at the center of the square.
void DrawEdgeTicks(Graphics& g, const RectF& rc, float inset, const ClockInk& k) {
    const float x0 = rc.X + inset;
    const float y0 = rc.Y + inset;
    const float w = rc.Width - 2.0f * inset;
    const float h = rc.Height - 2.0f * inset;
    const float perim = 2.0f * (w + h);
    const float cx = rc.X + rc.Width / 2.0f;
    const float cy = rc.Y + rc.Height / 2.0f;
    for (int i = 0; i < 60; ++i) {
        const float t = perim * i / 60.0f;
        float px = 0.0f, py = 0.0f;
        if (t < w) {
            px = x0 + t; py = y0;
        } else if (t < w + h) {
            px = x0 + w; py = y0 + (t - w);
        } else if (t < 2.0f * w + h) {
            px = x0 + w - (t - w - h); py = y0 + h;
        } else {
            px = x0; py = y0 + h - (t - 2.0f * w - h);
        }

        float dx = cx - px;
        float dy = cy - py;
        const float dist = std::sqrt(dx * dx + dy * dy);
        if (dist <= 0.0f) continue;
        dx /= dist;
        dy /= dist;

        const bool major = i % 5 == 0;
        const float len = major ? 9.0f : 4.0f;
        Pen pen(k.ticks, major ? 2.0f : 1.0f);
        g.DrawLine(&pen, px, py, px + dx * len, py + dy * len);
    }
}

// The time as h:mm in a condensed face. The digits are drawn as an outline and then shifted so
// the visible ink (not the font's advance box) is centered on (cx, cy).
void DrawDigits(Graphics& g, float cx, float cy, float size, int hour, int minute, const ClockInk& k) {
    FontFamily condensed(L"Bahnschrift Condensed");
    const int h12 = hour % 12 == 0 ? 12 : hour % 12;
    wchar_t text[8];
    swprintf_s(text, L"%d:%02d", h12, minute);

    GraphicsPath path;
    StringFormat format;
    path.AddString(text, -1, &condensed, FontStyleRegular, size, PointF(0.0f, 0.0f), &format);

    RectF bounds;
    path.GetBounds(&bounds);
    const float dx = cx - (bounds.X + bounds.Width / 2.0f);
    const float dy = cy - (bounds.Y + bounds.Height / 2.0f);

    GraphicsState state = g.Save();
    g.TranslateTransform(dx, dy);
    SolidBrush brush(k.text);
    g.FillPath(&brush, &path);
    g.Restore(state);
}

std::wstring FormatOffset(int minutes) {
    wchar_t buf[32];
    if (minutes % 60 == 0) {
        swprintf_s(buf, L"%+dHRS", minutes / 60);
    } else {
        swprintf_s(buf, L"%+.1fHRS", minutes / 60.0);
    }
    return buf;
}

std::wstring DayLabel(int dayDelta) {
    if (dayDelta == 0) return L"Today";
    if (dayDelta == 1) return L"Tomorrow";
    if (dayDelta == -1) return L"Yesterday";
    return L"";
}

// Builds the clock views: the PC's own time first, then each configured city.
ClockView MakeView(const WorldCity* city, const ZoneNow& pc) {
    ClockView v;
    if (city && city->valid) {
        const ZoneNow z = GetZoneNow(&city->tzi);
        v.code = city->code;
        v.name = city->name;
        v.t = z.local;
        v.relMin = z.offsetMin - pc.offsetMin;
        v.dayDelta = static_cast<int>(DaysFromCivil(z.local.wYear, z.local.wMonth, z.local.wDay) -
                                      DaysFromCivil(pc.local.wYear, pc.local.wMonth, pc.local.wDay));
        v.valid = true;
    } else {
        v.code = city ? city->code : L"LOCAL";
        v.name = city ? city->name : L"";
        v.t = pc.local;
        v.relMin = 0;
        v.dayDelta = 0;
        v.valid = city == nullptr;
    }
    return v;
}

void DrawClockLayout(Graphics& g, const RectF& rc, const ClockConfig& cc,
                     const std::vector<WorldCity>& cities, const ClockInk& ink,
                     bool darkText) {
    (void)darkText;
    FontFamily sans(L"Segoe UI");
    const ZoneNow pc = GetZoneNow(nullptr);
    const float r0 = std::min(rc.Width, rc.Height);

    switch (cc.layout) {
        case kClockDigital: {
            DrawEdgeTicks(g, rc, 8.0f, ink);
            DrawDigits(g, rc.X + rc.Width / 2.0f, rc.Y + rc.Height / 2.0f, 66.0f,
                       pc.local.wHour, pc.local.wMinute, ink);
            break;
        }
        case kClockCityDigital: {
            const ClockView v = MakeView(cities.empty() ? nullptr : &cities[0], pc);
            DrawEdgeTicks(g, rc, 8.0f, ink);
            DrawLabel(g, v.code.c_str(), sans, 10, FontStyleRegular,
                      RectF(rc.X, rc.Y + 16.0f, rc.Width, 16.0f),
                      StringAlignmentCenter, StringAlignmentCenter, ink.soft);
            DrawDigits(g, rc.X + rc.Width / 2.0f, rc.Y + 70.0f, 72.0f,
                       v.t.wHour, v.t.wMinute, ink);
            if (!cities.empty()) {
                DrawLabel(g, FormatOffset(v.relMin).c_str(), sans, 9, FontStyleRegular,
                          RectF(rc.X, rc.Y + 110.0f, rc.Width, 16.0f),
                          StringAlignmentCenter, StringAlignmentCenter, ink.soft);
            }
            break;
        }
        case kClockCityAnalog: {
            const ClockView v = MakeView(cities.empty() ? nullptr : &cities[0], pc);
            const float cx = rc.X + rc.Width / 2.0f;
            const float cy = rc.Y + rc.Height / 2.0f;
            const float r = r0 * 0.40f;
            DrawAnalogFace(g, cx, cy, r, ink, v.t.wHour, v.t.wMinute, v.t.wSecond, true, cc.secondHand);
            DrawLabel(g, v.code.c_str(), sans, r * 0.17f, FontStyleRegular,
                      RectF(cx - r * 0.6f, cy - r * 0.62f, r * 1.2f, r * 0.26f),
                      StringAlignmentCenter, StringAlignmentCenter, ink.soft);
            if (!cities.empty()) {
                DrawLabel(g, FormatOffset(v.relMin).c_str(), sans, r * 0.13f, FontStyleRegular,
                          RectF(cx - r * 0.7f, cy + r * 0.48f, r * 1.4f, r * 0.24f),
                          StringAlignmentCenter, StringAlignmentCenter, ink.soft);
            }
            break;
        }
        case kClockWorldGrid: {
            if (cities.empty()) {
                DrawLabel(g, L"Add cities in settings", sans, 8, FontStyleRegular,
                          RectF(rc.X + 8.0f, rc.Y + 60.0f, rc.Width - 16.0f, 24.0f),
                          StringAlignmentCenter, StringAlignmentCenter, ink.soft);
                break;
            }
            for (size_t i = 0; i < cities.size() && i < 4; ++i) {
                const ClockView v = MakeView(&cities[i], pc);
                const float cx = rc.X + rc.Width * ((i % 2) ? 0.75f : 0.25f);
                const float cy = rc.Y + rc.Height * ((i / 2) ? 0.75f : 0.25f);
                const float r = r0 * 0.19f;
                DrawAnalogFace(g, cx, cy, r, ink, v.t.wHour, v.t.wMinute, v.t.wSecond, false, false);
                DrawLabel(g, v.code.c_str(), sans, r * 0.30f, FontStyleRegular,
                          RectF(cx - r, cy - r * 0.62f, r * 2.0f, r * 0.3f),
                          StringAlignmentCenter, StringAlignmentCenter, ink.soft);
            }
            break;
        }
        case kClockWorldList: {
            if (cities.empty()) {
                DrawLabel(g, L"Add cities in settings", sans, 9, FontStyleRegular,
                          RectF(rc.X + 8.0f, rc.Y + 60.0f, rc.Width - 16.0f, 24.0f),
                          StringAlignmentCenter, StringAlignmentCenter, ink.soft);
                break;
            }
            // The dials and their labels form one block, centered in the widget. The dials sit
            // close together, and each dial is followed by its name, day, and offset.
            const size_t count = std::min<size_t>(cities.size(), 4);
            const float r = 26.0f;
            const float gap = 10.0f;
            const float pitch = 2.0f * r + gap;
            const float groupW = pitch * static_cast<float>(count) - gap;
            const float startX = rc.X + (rc.Width - groupW) / 2.0f;
            const float blockH = 2.0f * r + 52.0f;
            const float top = rc.Y + (rc.Height - blockH) / 2.0f;
            const float labelW = pitch + 14.0f;
            for (size_t i = 0; i < count; ++i) {
                const ClockView v = MakeView(&cities[i], pc);
                const float cx = startX + pitch * static_cast<float>(i) + r;
                const float cy = top + r;
                DrawAnalogFace(g, cx, cy, r, ink, v.t.wHour, v.t.wMinute, v.t.wSecond, false, false);
                DrawLabel(g, v.code.c_str(), sans, r * 0.32f, FontStyleRegular,
                          RectF(cx - r, cy - r * 0.5f, 2.0f * r, r * 0.4f),
                          StringAlignmentCenter, StringAlignmentCenter, ink.soft);
                DrawLabel(g, v.name.c_str(), sans, 10.5f, FontStyleBold,
                          RectF(cx - labelW / 2.0f, top + 2.0f * r + 8.0f, labelW, 16.0f),
                          StringAlignmentCenter, StringAlignmentCenter, ink.text);
                const std::wstring day = DayLabel(v.dayDelta);
                DrawLabel(g, day.c_str(), sans, 9.0f, FontStyleRegular,
                          RectF(cx - labelW / 2.0f, top + 2.0f * r + 24.0f, labelW, 14.0f),
                          StringAlignmentCenter, StringAlignmentCenter, ink.soft);
                DrawLabel(g, FormatOffset(v.relMin).c_str(), sans, 9.0f, FontStyleRegular,
                          RectF(cx - labelW / 2.0f, top + 2.0f * r + 38.0f, labelW, 14.0f),
                          StringAlignmentCenter, StringAlignmentCenter, ink.soft);
            }
            break;
        }
        case kClockAnalog:
        default: {
            const float cx = rc.X + rc.Width / 2.0f;
            const float cy = rc.Y + rc.Height / 2.0f;
            DrawAnalogFace(g, cx, cy, r0 * 0.42f, ink, pc.local.wHour, pc.local.wMinute, pc.local.wSecond,
                           true, cc.secondHand);
            break;
        }
    }
}

// ── Rendering ──

void DestroyRenderSurface() {
    if (g_renderSurface.memDc) {
        if (g_renderSurface.oldBitmap) SelectObject(g_renderSurface.memDc, g_renderSurface.oldBitmap);
        if (g_renderSurface.bitmap) DeleteObject(g_renderSurface.bitmap);
        DeleteDC(g_renderSurface.memDc);
    }
    g_renderSurface = {};
}

bool EnsureRenderSurface(HDC screenDc, int width, int height) {
    if (g_renderSurface.memDc && g_renderSurface.bitmap &&
        g_renderSurface.width == width && g_renderSurface.height == height) {
        return true;
    }
    DestroyRenderSurface();

    BITMAPINFO bi = {};
    bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bi.bmiHeader.biWidth = width;
    bi.bmiHeader.biHeight = -height;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;

    void* bits = nullptr;
    g_renderSurface.memDc = CreateCompatibleDC(screenDc);
    if (!g_renderSurface.memDc) return false;
    g_renderSurface.bitmap = CreateDIBSection(screenDc, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    if (!g_renderSurface.bitmap) {
        DestroyRenderSurface();
        return false;
    }
    g_renderSurface.oldBitmap = SelectObject(g_renderSurface.memDc, g_renderSurface.bitmap);
    g_renderSurface.bits = bits;
    ZeroMemory(bits, static_cast<size_t>(width) * height * 4);
    g_prevPresentRect = RECT{};
    g_fullRefresh = true;
    g_renderSurface.width = width;
    g_renderSurface.height = height;
    return true;
}

// Result of preparing a widget's glass background.
struct GlassResult {
    bool onGpu = false;  // the GPU drew the glass into buf.widget
    bool dark = false;   // the glass is bright enough that its text should be dark
};

// Fills buf.widget with the GPU glass for a slot. The result is cached per slot and reused while
// the wallpaper crop, size, and glass parameters are unchanged, so the GPU runs only when something
// visible changes. Returns onGpu = false when the CPU should draw the glass instead.
GlassResult PrepareGlassSlot(int slot, SlotBuffers& buf, const GlassSettings& gs, bool useGpu,
                             float s, float phase, int panelW, int panelH, int pad, int margin,
                             int cropX, int cropY, int bufW, int bufH) {
    GlassResult out;
    if (!useGpu || !g_gpu.ready) return out;

    const int cropW = bufW + 2 * margin;
    const int cropH = bufH + 2 * margin;
    const bool cropChanged = UpdateCrop(buf, cropX, cropY, cropW, cropH);
    const GlassCB cb = MakeGlassParams(gs, s, phase, panelW, panelH, pad, margin, cropW, cropH);
    const size_t n = static_cast<size_t>(bufW) * static_cast<size_t>(bufH);

    const bool reuse = buf.glassValid && !cropChanged && buf.glass.size() == n &&
                       std::memcmp(&buf.glassCb, &cb, sizeof(GlassCB)) == 0;
    if (!reuse) {
        if (buf.glass.size() != n) buf.glass.assign(n, 0u);
        const bool ok = GpuRenderGlass(g_gpu.targets[slot], cb, buf.crop, cropW, cropH,
                                       buf.glass, bufW, bufH);
        buf.glassValid = ok;
        buf.glassCb = cb;
        if (!ok) {
            ReleaseGpu();
            return out;
        }
        buf.glassDark = ShouldUseDarkText(buf.glass, bufW, pad, panelW, panelH);
    }

    if (buf.widget.size() != n) buf.widget.assign(n, 0u);
    std::memcpy(buf.widget.data(), buf.glass.data(), n * sizeof(uint32_t));
    out.onGpu = true;
    out.dark = buf.glassDark;
    return out;
}

// Composites a premultiplied widget buffer over the surface ("source over"). The transparent
// shadow padding of one widget therefore never erases a neighbour's pixels.
void BlitPremultiplied(const std::vector<uint32_t>& src, int srcW, int srcH,
                       uint8_t* dst, int dstW, int dstH, int dstX, int dstY) {
    const int x0 = std::max(0, -dstX);
    const int x1 = std::min(srcW, dstW - dstX);
    if (x1 <= x0) return;
    for (int y = 0; y < srcH; ++y) {
        const int dy = dstY + y;
        if (dy < 0 || dy >= dstH) continue;
        const uint32_t* s = src.data() + static_cast<size_t>(y) * srcW;
        uint32_t* d = reinterpret_cast<uint32_t*>(dst) + static_cast<size_t>(dy) * dstW + dstX;
        for (int x = x0; x < x1; ++x) {
            const uint32_t sp = s[x];
            const uint32_t sa = sp >> 24;
            if (sa == 0) continue;
            if (sa == 255) {
                d[x] = sp;
                continue;
            }
            const uint32_t inv = 255u - sa;
            const uint32_t dp = d[x];
            uint32_t out = 0;
            for (int shift = 0; shift < 32; shift += 8) {
                uint32_t v = ((sp >> shift) & 0xFFu) + (((dp >> shift) & 0xFFu) * inv + 127u) / 255u;
                if (v > 255u) v = 255u;
                out |= v << shift;
            }
            d[x] = out;
        }
    }
}

void ApplyAnimationTimer(const WeatherConfig& cfg) {
    if (!g_hwnd) return;
    if (cfg.glass.animate && cfg.useGpu && g_gpu.ready && SlotEnabled(kWeatherSlot)) {
        SetTimer(g_hwnd, kAnimTimerId, static_cast<UINT>(1000 / cfg.glass.fps), nullptr);
    } else {
        KillTimer(g_hwnd, kAnimTimerId);
    }
}

// Redraws the countdown and advances the Pomodoro once per second while either is enabled.
// One timer drives every time-based redraw. It runs each second while a seconds display or a
// countdown needs it, every 15 seconds for a clock that shows only minutes, and not at all otherwise.
void ApplyFocusTimer(const ClockConfig& cc) {
    if (!g_hwnd) return;
    const bool needsSeconds = SlotEnabled(kCountdownSlot) || SlotEnabled(kPomodoroSlot) ||
                              SlotEnabled(kTimerSlot) || (SlotEnabled(kClockSlot) && cc.secondHand);
    if (needsSeconds) {
        SetTimer(g_hwnd, kFocusTimerId, 1000, nullptr);
    } else if (SlotEnabled(kClockSlot)) {
        SetTimer(g_hwnd, kFocusTimerId, kClockSlowMs, nullptr);
    } else {
        KillTimer(g_hwnd, kFocusTimerId);
    }
    KillTimer(g_hwnd, kClockTimerId);  // retired: the focus timer above replaces it
}

void ApplyClockTimer(const ClockConfig& cc) {
    ApplyFocusTimer(cc);
}

void RenderWeatherSlot(uint8_t* bits, int surfW, int surfH) {
    const WeatherConfig cfg = SnapshotWeather();
    WeatherData data;
    {
        std::lock_guard<std::mutex> lock(g_mutex);
        data = g_weather;
    }

    const float s = SlotScale(kWeatherSlot);
    const int glassW = static_cast<int>(std::lround(kWeatherW * s));
    const float weatherH = WeatherWidgetHeight();
    const int glassH = static_cast<int>(std::lround(weatherH * s));
    const int pad = static_cast<int>(std::ceil(kShadowPad * s));
    const int margin = static_cast<int>(std::ceil(kSampleMargin * s));
    const int bufW = glassW + 2 * pad;
    const int bufH = glassH + 2 * pad;
    const int cropW = bufW + 2 * margin;
    const int cropH = bufH + 2 * margin;

    const RECT wa = DesktopWorkArea();
    const int wx = static_cast<int>(std::lround(SlotRc(kWeatherSlot).X * s));
    const int wy = static_cast<int>(std::lround(SlotRc(kWeatherSlot).Y * s));

    SlotBuffers& buf = g_buffers[kWeatherSlot];
    if (buf.widget.size() != static_cast<size_t>(bufW) * bufH) {
        buf.widget.assign(static_cast<size_t>(bufW) * bufH, 0u);
    }

    const GlassResult gr = PrepareGlassSlot(kWeatherSlot, buf, cfg.glass, cfg.useGpu, s, SheenPhase(cfg),
                                            glassW, glassH, pad, margin,
                                            wa.left + wx - pad - margin, wa.top + wy - pad - margin,
                                            bufW, bufH);
    const bool glassOnGpu = gr.onGpu;
    const bool darkText = gr.dark;
    if (!glassOnGpu && cfg.glass.animate) ApplyAnimationTimer(cfg);
    if (!glassOnGpu) std::fill(buf.widget.begin(), buf.widget.end(), 0u);

    {
        Bitmap widgetBmp(bufW, bufH, bufW * 4, PixelFormat32bppPARGB,
                         reinterpret_cast<BYTE*>(buf.widget.data()));
        Graphics gw(&widgetBmp);
        gw.SetSmoothingMode(SmoothingModeAntiAlias);
        gw.SetTextRenderingHint(TextRenderingHintAntiAliasGridFit);
        gw.ScaleTransform(s, s);

        const float pl = static_cast<float>(pad) / s;
        const RectF rcLocal(pl, pl, kWeatherW, weatherH);
        if (!glassOnGpu) DrawGlassPanel(gw, rcLocal, kCornerRadius);
        DrawWeatherWidget(gw, rcLocal, cfg, data, darkText);
    }

    BlitPremultiplied(buf.widget, bufW, bufH, bits, surfW, surfH, wx - pad, wy - pad);
}

// Upcoming and agenda lists depend only on the events, today, and the layout, so they are
// rebuilt only when one of those changes rather than on every redraw.
struct CalendarCache {
    bool valid = false;
    uint64_t version = 0;
    int64_t day = 0;
    int layout = -1;
    std::vector<UpcomingItem> upcoming;
    std::vector<std::vector<AgendaItem>> agenda;
};
CalendarCache g_calCache;  // UI thread only

void RenderCalendarSlot(uint8_t* bits, int surfW, int surfH) {
    const CalendarConfig cfg = SnapshotCalendar();
    const WeatherConfig wcfg = SnapshotWeather();
    const EventSnapshot snap = SnapshotEvents();

    SYSTEMTIME today;
    GetLocalTime(&today);
    g_lastDayKey = today.wYear * 10000 + today.wMonth * 100 + today.wDay;

    const int layout = g_calLayout.load();
    const RectF box = SlotBox(kCalendarSlot);
    const float s = SlotScale(kCalendarSlot);
    const int panelW = static_cast<int>(std::lround(box.Width * s));
    const int panelH = static_cast<int>(std::lround(box.Height * s));
    const int pad = static_cast<int>(std::ceil(kShadowPad * s));
    const int margin = static_cast<int>(std::ceil(kSampleMargin * s));
    const int bufW = panelW + 2 * pad;
    const int bufH = panelH + 2 * pad;
    const int cropW = bufW + 2 * margin;
    const int cropH = bufH + 2 * margin;

    const RECT wa = DesktopWorkArea();
    const int wx = static_cast<int>(std::lround(SlotRc(kCalendarSlot).X * s));
    const int wy = static_cast<int>(std::lround(SlotRc(kCalendarSlot).Y * s));

    SlotBuffers& buf = g_buffers[kCalendarSlot];
    if (buf.widget.size() != static_cast<size_t>(bufW) * bufH) {
        buf.widget.assign(static_cast<size_t>(bufW) * bufH, 0u);
    }

    const int64_t cacheDay = DaysFromCivil(today.wYear, today.wMonth, today.wDay);
    if (!g_calCache.valid || g_calCache.version != snap.version ||
        g_calCache.day != cacheDay || g_calCache.layout != layout) {
        g_calCache.valid = true;
        g_calCache.version = snap.version;
        g_calCache.day = cacheDay;
        g_calCache.layout = layout;
        g_calCache.upcoming.clear();
        g_calCache.agenda.clear();
        if (layout == kLayoutUpcoming) {
            g_calCache.upcoming = CollectUpcoming(EventsOf(snap), cacheDay,
                                                  cacheDay + kUpcomingWindowDays, kUpcomingRows);
        } else if (layout == kLayoutAgenda) {
            g_calCache.agenda = CollectAgenda(EventsOf(snap), cacheDay, kAgendaDays);
        } else if (layout == kLayoutToday) {
            g_calCache.agenda = CollectAgenda(EventsOf(snap), cacheDay, 1);
        }
    }

    const GlassResult gr = PrepareGlassSlot(kCalendarSlot, buf, wcfg.glass, cfg.glass && wcfg.useGpu,
                                            s, -1.0f, panelW, panelH, pad, margin,
                                            wa.left + wx - pad - margin, wa.top + wy - pad - margin,
                                            bufW, bufH);
    const bool glassOnGpu = gr.onGpu;
    const bool darkText = gr.dark;
    if (!glassOnGpu) std::fill(buf.widget.begin(), buf.widget.end(), 0u);

    {
        Bitmap bmp(bufW, bufH, bufW * 4, PixelFormat32bppPARGB, reinterpret_cast<BYTE*>(buf.widget.data()));
        Graphics g(&bmp);
        g.SetSmoothingMode(SmoothingModeAntiAlias);
        g.SetTextRenderingHint(TextRenderingHintAntiAliasGridFit);
        g.ScaleTransform(s, s);

        const float pl = static_cast<float>(pad) / s;
        const RectF rcLocal(pl, pl, box.Width, box.Height);
        if (!glassOnGpu) {
            if (cfg.glass) DrawGlassPanel(g, rcLocal, kCornerRadius);
            else DrawDarkPanel(g, rcLocal, kCornerRadius);
        }

        const Ink ink = MakeInk(cfg.glass, darkText);
        const int64_t todayDay = DaysFromCivil(today.wYear, today.wMonth, today.wDay);
        const std::vector<bool>& marks = MarksFor(today.wYear, today.wMonth, snap);

        switch (layout) {
            case kLayoutUpcoming: {
                const std::vector<UpcomingItem>& items = g_calCache.upcoming;
                DrawUpcomingList(g, pl, pl, items, ink, snap.status);
                DrawMonthGrid(g, pl, pl, kUpcomingGridX, kUpcomingGridW, today, marks,
                              cfg.showDots, ink, FetchStatus::Ok);
                break;
            }
            case kLayoutAgenda: {
                const auto& days = g_calCache.agenda;
                DrawAgendaList(g, pl, pl, days, todayDay, today, ink, snap.status);
                break;
            }
            case kLayoutToday: {
                const auto& days = g_calCache.agenda;
                DrawTodayPanel(g, pl, pl, days[0], today, ink, snap.status);
                break;
            }
            default:
                DrawMonthGrid(g, pl, pl, kPadX, kMonthW - 2.0f * kPadX, today, marks,
                              cfg.showDots, ink, snap.status);
                break;
        }
    }

    BlitPremultiplied(buf.widget, bufW, bufH, bits, surfW, surfH, wx - pad, wy - pad);
}

void RenderClockSlot(uint8_t* bits, int surfW, int surfH) {
    const ClockConfig cc = SnapshotClock();
    const WeatherConfig wcfg = SnapshotWeather();
    const std::vector<WorldCity> cities = SnapshotCities();

    const RectF box = SlotBox(kClockSlot);
    const float s = SlotScale(kClockSlot);
    const int panelW = static_cast<int>(std::lround(box.Width * s));
    const int panelH = static_cast<int>(std::lround(box.Height * s));
    const int pad = static_cast<int>(std::ceil(kShadowPad * s));
    const int margin = static_cast<int>(std::ceil(kSampleMargin * s));
    const int bufW = panelW + 2 * pad;
    const int bufH = panelH + 2 * pad;
    const int cropW = bufW + 2 * margin;
    const int cropH = bufH + 2 * margin;

    const RECT wa = DesktopWorkArea();
    const int wx = static_cast<int>(std::lround(SlotRc(kClockSlot).X * s));
    const int wy = static_cast<int>(std::lround(SlotRc(kClockSlot).Y * s));

    SlotBuffers& buf = g_buffers[kClockSlot];
    if (buf.widget.size() != static_cast<size_t>(bufW) * bufH) {
        buf.widget.assign(static_cast<size_t>(bufW) * bufH, 0u);
    }

    const bool glass = cc.style == kStyleGlass;
    const GlassResult gr = PrepareGlassSlot(kClockSlot, buf, wcfg.glass, glass && wcfg.useGpu,
                                            s, -1.0f, panelW, panelH, pad, margin,
                                            wa.left + wx - pad - margin, wa.top + wy - pad - margin,
                                            bufW, bufH);
    const bool glassOnGpu = gr.onGpu;
    const bool darkText = gr.dark;
    if (!glassOnGpu) std::fill(buf.widget.begin(), buf.widget.end(), 0u);

    {
        Bitmap bmp(bufW, bufH, bufW * 4, PixelFormat32bppPARGB, reinterpret_cast<BYTE*>(buf.widget.data()));
        Graphics g(&bmp);
        g.SetSmoothingMode(SmoothingModeAntiAlias);
        g.SetTextRenderingHint(TextRenderingHintAntiAliasGridFit);
        g.ScaleTransform(s, s);

        const float pl = static_cast<float>(pad) / s;
        const RectF rcLocal(pl, pl, box.Width, box.Height);
        if (!glassOnGpu) {
            if (glass) DrawGlassPanel(g, rcLocal, kCornerRadius);
            else if (cc.style == kStyleLight) DrawLightPanel(g, rcLocal, kCornerRadius);
            else DrawDarkPanel(g, rcLocal, kCornerRadius);
        }

        const ClockInk ink = MakeClockInk(cc.style, darkText);
        DrawClockLayout(g, rcLocal, cc, cities, ink, darkText);
    }

    BlitPremultiplied(buf.widget, bufW, bufH, bits, surfW, surfH, wx - pad, wy - pad);
}

bool RssScrollMetrics(float& trackY, float& trackH, float& thumbY, float& thumbH, int& maxScroll) {
    std::shared_ptr<const std::vector<RssItem>> items;
    { std::lock_guard<std::mutex> lock(g_mutex); items = g_rssItems; }
    const RectF box = SlotBox(kRssSlot);
    const int total = items ? static_cast<int>(items->size()) : 0;
    const int visible = std::max(1, std::min(total, static_cast<int>((box.Height - kRssHeaderH - 12.0f) / kRssRowH)));
    maxScroll = std::max(0, total - visible);
    if (maxScroll == 0) return false;
    trackY = kRssHeaderH;
    trackH = std::max(10.0f, box.Height - kRssHeaderH - 8.0f);
    thumbH = std::max(18.0f, trackH * visible / total);
    thumbY = trackY + (trackH - thumbH) * std::clamp(g_rssScroll.load(), 0, maxScroll) / maxScroll;
    return true;
}

void RenderRssSlot(uint8_t* bits, int surfW, int surfH) {
    const RssConfig cfg = SnapshotRss();
    std::shared_ptr<const std::vector<RssItem>> items;
    FetchStatus status;
    std::wstring feedTitle;
    { std::lock_guard<std::mutex> lock(g_mutex); items = g_rssItems; feedTitle = g_rssFeedTitle; status = g_rssStatus; }
    const RectF box = SlotBox(kRssSlot);
    const float s = SlotScale(kRssSlot);
    const int panelW = static_cast<int>(std::lround(box.Width * s));
    const int panelH = static_cast<int>(std::lround(box.Height * s));
    const int pad = static_cast<int>(std::ceil(kShadowPad * s));
    const int bufW = panelW + 2 * pad, bufH = panelH + 2 * pad;
    const int margin = static_cast<int>(std::ceil(kSampleMargin * s));
    const int cropW = bufW + 2 * margin, cropH = bufH + 2 * margin;
    const RECT wa = DesktopWorkArea();
    const int wx = static_cast<int>(std::lround(SlotRc(kRssSlot).X * s));
    const int wy = static_cast<int>(std::lround(SlotRc(kRssSlot).Y * s));
    SlotBuffers& buf = g_buffers[kRssSlot];
    if (buf.widget.size() != static_cast<size_t>(bufW) * bufH) buf.widget.assign(static_cast<size_t>(bufW) * bufH, 0u);
    const WeatherConfig wc = SnapshotWeather();
    const GlassResult gr = PrepareGlassSlot(kRssSlot, buf, wc.glass, wc.useGpu, s, -1.0f,
                                            panelW, panelH, pad, margin,
                                            wa.left + wx - pad - margin, wa.top + wy - pad - margin,
                                            bufW, bufH);
    const bool glassOnGpu = gr.onGpu;
    const bool darkText = gr.dark;
    if (!glassOnGpu) std::fill(buf.widget.begin(), buf.widget.end(), 0u);
    {
        Bitmap bmp(bufW, bufH, bufW * 4, PixelFormat32bppPARGB, reinterpret_cast<BYTE*>(buf.widget.data()));
        Graphics g(&bmp); g.SetSmoothingMode(SmoothingModeAntiAlias); g.SetTextRenderingHint(TextRenderingHintAntiAliasGridFit); g.ScaleTransform(s, s);
        const float pl = static_cast<float>(pad) / s;
        RectF rc(pl, pl, box.Width, box.Height);
        if (!glassOnGpu) DrawGlassPanel(g, rc, kCornerRadius);
        const Color main(255, GetRValue(cfg.textColor), GetGValue(cfg.textColor), GetBValue(cfg.textColor));
        const Color soft(245, GetRValue(cfg.textColor), GetGValue(cfg.textColor), GetBValue(cfg.textColor));
        FontFamily family(L"Segoe UI");
        const wchar_t* headerText = feedTitle.empty() ? L"RSS FEED" : feedTitle.c_str();
        DrawRssLabel(g, headerText, family, 10.0f, FontStyleBold,
                     RectF(rc.X + 14, rc.Y + 12, rc.Width - 28, 16), main, cfg.textShadow);
        const int total = items ? static_cast<int>(items->size()) : 0;
        const int visible = std::max(1, std::min(total, static_cast<int>((box.Height - kRssHeaderH - 12.0f) / kRssRowH)));
        const int maxScroll = std::max(0, total - visible);
        const int first = std::clamp(g_rssScroll.load(), 0, maxScroll);
        g_rssScroll = first;
        if (total == 0) {
            const wchar_t* msg = status == FetchStatus::NoUrl ? L"Set an RSS feed URL in settings" : (status == FetchStatus::Failed ? L"Unable to load feed" : L"Loading headlines...");
            DrawRssLabel(g, msg, family, 10.0f, FontStyleRegular,
                         RectF(rc.X + 14, rc.Y + 40, rc.Width - 28, 30), soft, cfg.textShadow);
        } else {
            const int rows = std::min(visible, total - first);
            for (int i = 0; i < rows; ++i) {
                const float y = rc.Y + kRssHeaderH + i * kRssRowH;
                if (i > 0) { Pen sep(Color(55, 255, 255, 255), 1.0f); g.DrawLine(&sep, rc.X + 13, y, rc.X + rc.Width - 16, y); }
                // Keep the text within the panel's inner border and reserve the right edge
                // for the scrollbar. Word wrapping is confined to this headline's row.
                DrawRssRowText(g, (*items)[static_cast<size_t>(first + i)].title.c_str(), family,
                               RectF(rc.X + 14, y + 1.5f, rc.Width - 36, kRssRowH - 3.0f), main, cfg.textShadow);
            }
            if (maxScroll > 0) {
                const float trackX = rc.X + rc.Width - 12.0f;
                const float trackY = rc.Y + kRssHeaderH;
                const float trackH = std::max(10.0f, rc.Height - kRssHeaderH - 8.0f);
                const float thumbH = std::max(18.0f, trackH * visible / total);
                const float thumbY = trackY + (trackH - thumbH) * first / maxScroll;
                SolidBrush track(Color(45, 255, 255, 255)); g.FillRectangle(&track, trackX, trackY, 3.0f, trackH);
                SolidBrush thumb(Color(170, 255, 255, 255)); g.FillRectangle(&thumb, trackX - 1.5f, thumbY, 6.0f, thumbH);
            }
        }
    }
    BlitPremultiplied(buf.widget, bufW, bufH, bits, surfW, surfH, wx - pad, wy - pad);
}

// ── Countdown and Pomodoro: rendering and state ──

CountdownConfig SnapshotCountdown() {
    std::lock_guard<std::mutex> lock(g_mutex);
    return g_countdownCfg;
}

PomodoroConfig SnapshotPomodoro() {
    std::lock_guard<std::mutex> lock(g_mutex);
    return g_pomodoroCfg;
}

int64_t PomodoroDurationMs(bool work, const PomodoroConfig& cfg) {
    return static_cast<int64_t>(work ? cfg.workMin : cfg.breakMin) * 60 * 1000;
}

void ResetPomodoro() {
    const PomodoroConfig cfg = SnapshotPomodoro();
    g_pomo.initialized = true;
    g_pomo.running = false;
    g_pomo.work = true;
    g_pomo.remainingMs = PomodoroDurationMs(true, cfg);
    g_pomo.completed = 0;
}

// Advances the timer by the time since the last update. When a focus or break period ends, the
// timer stops and switches to the other phase, so the next period starts on a click.
void UpdatePomodoro() {
    if (!g_pomo.initialized) ResetPomodoro();
    if (!g_pomo.running) return;

    const ULONGLONG now = GetTickCount64();
    g_pomo.remainingMs -= static_cast<int64_t>(now - g_pomo.lastTickMs);
    g_pomo.lastTickMs = now;
    if (g_pomo.remainingMs > 0) return;

    if (g_pomo.work) ++g_pomo.completed;
    g_pomo.work = !g_pomo.work;
    g_pomo.remainingMs = PomodoroDurationMs(g_pomo.work, SnapshotPomodoro());
    g_pomo.running = false;
}

void TogglePomodoro() {
    UpdatePomodoro();
    if (g_pomo.running) {
        g_pomo.running = false;
    } else {
        g_pomo.running = true;
        g_pomo.lastTickMs = GetTickCount64();
    }
}

// Runs after settings change. A running timer keeps its place. An idle one takes the new length
// of its current phase. A disabled widget pauses so it stops counting.
void SyncPomodoroToSettings() {
    if (!g_pomo.initialized) {
        ResetPomodoro();
        return;
    }
    UpdatePomodoro();
    if (!SlotEnabled(kPomodoroSlot)) g_pomo.running = false;
    if (!g_pomo.running) {
        g_pomo.remainingMs = PomodoroDurationMs(g_pomo.work, SnapshotPomodoro());
    }
}

// Draws a glass or dark panel into a widget slot and then calls `draw` to paint its contents.
// The text color follows the glass: dark text on bright glass, light text otherwise.
template <typename DrawFn>
void RenderPanelSlot(int slot, bool glass, uint8_t* bits, int surfW, int surfH, const RectF& box, DrawFn&& draw) {
    const WeatherConfig wc = SnapshotWeather();
    const float s = SlotScale(slot);
    const int panelW = static_cast<int>(std::lround(box.Width * s));
    const int panelH = static_cast<int>(std::lround(box.Height * s));
    const int pad = static_cast<int>(std::ceil(kShadowPad * s));
    const int margin = static_cast<int>(std::ceil(kSampleMargin * s));
    const int bufW = panelW + 2 * pad;
    const int bufH = panelH + 2 * pad;
    const int cropW = bufW + 2 * margin;
    const int cropH = bufH + 2 * margin;
    const RECT wa = DesktopWorkArea();
    const int wx = static_cast<int>(std::lround(SlotRc(slot).X * s));
    const int wy = static_cast<int>(std::lround(SlotRc(slot).Y * s));

    SlotBuffers& buf = g_buffers[slot];
    if (buf.widget.size() != static_cast<size_t>(bufW) * bufH) {
        buf.widget.assign(static_cast<size_t>(bufW) * bufH, 0u);
    }

    const GlassResult gr = PrepareGlassSlot(slot, buf, wc.glass, glass && wc.useGpu, s, -1.0f,
                                            panelW, panelH, pad, margin,
                                            wa.left + wx - pad - margin, wa.top + wy - pad - margin,
                                            bufW, bufH);
    const bool glassOnGpu = gr.onGpu;
    const bool darkText = gr.dark;
    if (!glassOnGpu) std::fill(buf.widget.begin(), buf.widget.end(), 0u);

    {
        Bitmap bmp(bufW, bufH, bufW * 4, PixelFormat32bppPARGB, reinterpret_cast<BYTE*>(buf.widget.data()));
        Graphics g(&bmp);
        g.SetSmoothingMode(SmoothingModeAntiAlias);
        g.SetTextRenderingHint(TextRenderingHintAntiAliasGridFit);
        g.ScaleTransform(s, s);

        const float pl = static_cast<float>(pad) / s;
        const RectF rc(pl, pl, box.Width, box.Height);
        if (!glassOnGpu) {
            if (glass) DrawGlassPanel(g, rc, kCornerRadius);
            else DrawDarkPanel(g, rc, kCornerRadius);
        }
        const bool dark = glass && darkText;
        const Color text = dark ? Color(245, 22, 26, 34) : Color(245, 255, 255, 255);
        const Color soft = dark ? Color(190, 22, 26, 34) : Color(190, 255, 255, 255);
        draw(g, rc, text, soft);
    }

    BlitPremultiplied(buf.widget, bufW, bufH, bits, surfW, surfH, wx - pad, wy - pad);
}

void RenderCountdownSlot(uint8_t* bits, int surfW, int surfH) {
    const CountdownConfig cfg = SnapshotCountdown();
    RenderPanelSlot(kCountdownSlot, cfg.glass, bits, surfW, surfH, SlotBox(kCountdownSlot),
        [&cfg](Graphics& g, const RectF& rc, Color text, Color soft) {
            FontFamily sans(L"Segoe UI");
            FontFamily light(L"Segoe UI Light");

            DrawLabel(g, cfg.title.c_str(), sans, 10.0f, FontStyleBold,
                      RectF(rc.X + 14.0f, rc.Y + 12.0f, rc.Width - 28.0f, 14.0f),
                      StringAlignmentNear, StringAlignmentCenter, text);

            if (cfg.status != kCdOk) {
                const wchar_t* message = cfg.status == kCdInvalid ? L"Use YYYY-MM-DD HH:MM" : L"Set a date in settings";
                DrawLabel(g, message, sans, 9.0f, FontStyleRegular,
                          RectF(rc.X + 10.0f, rc.Y + 56.0f, rc.Width - 20.0f, 32.0f),
                          StringAlignmentCenter, StringAlignmentCenter, soft);
                return;
            }

            const int64_t remaining = cfg.targetTicks - NowFileTimeTicks();
            if (remaining <= 0) {
                DrawLabel(g, L"Reached", light, 26.0f, FontStyleRegular,
                          RectF(rc.X, rc.Y + 44.0f, rc.Width, 40.0f),
                          StringAlignmentCenter, StringAlignmentCenter, text);
            } else {
                const long long secs = remaining / 10000000LL;
                const long long days = secs / 86400;
                const long long hours = (secs % 86400) / 3600;
                const long long mins = (secs % 3600) / 60;
                const long long sec = secs % 60;

                wchar_t dayText[24];
                swprintf_s(dayText, L"%lld", days);
                DrawLabel(g, dayText, light, 44.0f, FontStyleRegular,
                          RectF(rc.X, rc.Y + 26.0f, rc.Width, 50.0f),
                          StringAlignmentCenter, StringAlignmentCenter, text);
                DrawLabel(g, days == 1 ? L"DAY" : L"DAYS", sans, 9.0f, FontStyleBold,
                          RectF(rc.X, rc.Y + 76.0f, rc.Width, 14.0f),
                          StringAlignmentCenter, StringAlignmentCenter, soft);

                wchar_t clockText[24];
                swprintf_s(clockText, L"%02lld:%02lld:%02lld", hours, mins, sec);
                DrawLabel(g, clockText, sans, 13.0f, FontStyleRegular,
                          RectF(rc.X, rc.Y + 94.0f, rc.Width, 18.0f),
                          StringAlignmentCenter, StringAlignmentCenter, text);
            }

            DrawLabel(g, cfg.targetLabel.c_str(), sans, 8.0f, FontStyleRegular,
                      RectF(rc.X + 6.0f, rc.Y + 124.0f, rc.Width - 12.0f, 14.0f),
                      StringAlignmentCenter, StringAlignmentCenter, soft);
        });
}

void RenderPomodoroSlot(uint8_t* bits, int surfW, int surfH) {
    UpdatePomodoro();
    const PomodoroConfig cfg = SnapshotPomodoro();
    const PomodoroState st = g_pomo;
    RenderPanelSlot(kPomodoroSlot, cfg.glass, bits, surfW, surfH, SlotBox(kPomodoroSlot),
        [&cfg, &st](Graphics& g, const RectF& rc, Color text, Color soft) {
            FontFamily sans(L"Segoe UI");
            FontFamily light(L"Segoe UI Light");
            const Color accent = st.work ? Color(255, 255, 110, 80) : Color(255, 90, 200, 140);

            // Progress ring: the arc fills as the current focus or break period runs down.
            const int64_t total = PomodoroDurationMs(st.work, cfg);
            const float fraction = total > 0
                ? Clamp(1.0f - static_cast<float>(st.remainingMs) / static_cast<float>(total), 0.0f, 1.0f)
                : 0.0f;
            const float cx = rc.X + rc.Width / 2.0f;
            const float cy = rc.Y + rc.Height / 2.0f;
            const float r = 50.0f;
            Pen track(Color(60, soft.GetR(), soft.GetG(), soft.GetB()), 4.0f);
            g.DrawEllipse(&track, cx - r, cy - r, 2.0f * r, 2.0f * r);
            if (fraction > 0.0f) {
                Pen arc(accent, 4.0f);
                arc.SetStartCap(LineCapRound);
                arc.SetEndCap(LineCapRound);
                g.DrawArc(&arc, cx - r, cy - r, 2.0f * r, 2.0f * r, -90.0f, 360.0f * fraction);
            }

            DrawLabel(g, st.work ? L"FOCUS" : L"BREAK", sans, 9.0f, FontStyleBold,
                      RectF(rc.X, cy - 36.0f, rc.Width, 14.0f),
                      StringAlignmentCenter, StringAlignmentCenter, accent);

            const long long secsLeft = std::max<long long>(0, (st.remainingMs + 999) / 1000);
            wchar_t timeText[16];
            swprintf_s(timeText, L"%02lld:%02lld", secsLeft / 60, secsLeft % 60);
            DrawLabel(g, timeText, light, 34.0f, FontStyleRegular,
                      RectF(rc.X, cy - 22.0f, rc.Width, 42.0f),
                      StringAlignmentCenter, StringAlignmentCenter, text);

            wchar_t doneText[32];
            swprintf_s(doneText, L"Done: %d", st.completed);
            DrawLabel(g, doneText, sans, 8.5f, FontStyleRegular,
                      RectF(rc.X, cy + 24.0f, rc.Width, 13.0f),
                      StringAlignmentCenter, StringAlignmentCenter, soft);
            DrawLabel(g, st.running ? L"Click to pause" : L"Click to start", sans, 7.5f, FontStyleRegular,
                      RectF(rc.X, cy + 38.0f, rc.Width, 12.0f),
                      StringAlignmentCenter, StringAlignmentCenter, soft);
        });
}

// ── Timer: state, layout, and rendering ──

enum TimerAction {
    kTimerNone = -1,
    kTimerStart,
    kTimerStop,
    kTimerReset,
    kTimerPreset0,
    kTimerPreset1,
    kTimerPreset2,
    kTimerCustom,
};

struct TimerButton {
    TimerAction action;
    RectF rc;  // widget-local logical coordinates
};

TimerConfig SnapshotTimer() {
    std::lock_guard<std::mutex> lock(g_mutex);
    return g_timerCfg;
}

// Length in milliseconds for a selection index: 0 to 2 are the presets, and 3 is the custom length.
int64_t TimerDurationMs(int selected, const TimerConfig& cfg) {
    static const int64_t kPresetMs[3] = {5 * 60 * 1000, 10 * 60 * 1000, 15 * 60 * 1000};
    if (selected < 3) return kPresetMs[selected];
    return static_cast<int64_t>(cfg.customMin) * 60 * 1000;
}

void EnsureTimerInit() {
    if (g_timer.initialized) return;
    g_timer.initialized = true;
    g_timer.durationMs = TimerDurationMs(g_timer.selected, SnapshotTimer());
    g_timer.remainingMs = g_timer.durationMs;
}

// Advances the countdown by the time since the last update. Reaching zero stops the timer and
// marks it finished.
void UpdateTimer() {
    EnsureTimerInit();
    if (!g_timer.running) return;

    const ULONGLONG now = GetTickCount64();
    g_timer.remainingMs -= static_cast<int64_t>(now - g_timer.lastTickMs);
    g_timer.lastTickMs = now;
    if (g_timer.remainingMs <= 0) {
        g_timer.remainingMs = 0;
        g_timer.running = false;
        g_timer.finished = true;
        if (g_hwnd) PostMessageW(g_hwnd, kTimerDoneMessage, 0, 0);
    }
}

void StartTimer() {
    UpdateTimer();
    if (g_timer.running) return;
    if (g_timer.remainingMs <= 0) g_timer.remainingMs = g_timer.durationMs;
    g_timer.finished = false;
    g_timer.running = true;
    g_timer.lastTickMs = GetTickCount64();
}

// Pauses the timer. Start resumes it from the same point.
void StopTimer() {
    UpdateTimer();
    g_timer.running = false;
}

void ResetTimer() {
    EnsureTimerInit();
    g_timer.running = false;
    g_timer.finished = false;
    g_timer.remainingMs = g_timer.durationMs;
}

// Chooses a preset or the custom length. A running timer is stopped and set to the new length.
void SelectTimerPreset(int index) {
    EnsureTimerInit();
    g_timer.running = false;
    g_timer.selected = index;
    g_timer.durationMs = TimerDurationMs(index, SnapshotTimer());
    g_timer.remainingMs = g_timer.durationMs;
    g_timer.finished = false;
}

// Runs after settings change. A custom length takes the new value. An idle timer shows the new
// length, and a running one keeps its place.
void SyncTimerToSettings() {
    if (!g_timer.initialized) {
        EnsureTimerInit();
        return;
    }
    UpdateTimer();
    if (g_timer.running) return;
    g_timer.durationMs = TimerDurationMs(g_timer.selected, SnapshotTimer());
    if (!g_timer.finished) g_timer.remainingMs = g_timer.durationMs;
}

// Button and chip positions in widget-local logical units. Drawing and clicks both use this list.
std::vector<TimerButton> TimerButtons() {
    const float pad = 16.0f;
    const float gap = 6.0f;
    std::vector<TimerButton> out;

    // Preset chips across the middle, with the Start, Stop, and Reset controls below them.
    const float chipW = (kTimerW - 2.0f * pad - 3.0f * gap) / 4.0f;
    const TimerAction chips[4] = {kTimerPreset0, kTimerPreset1, kTimerPreset2, kTimerCustom};
    for (int i = 0; i < 4; ++i) {
        out.push_back(TimerButton{chips[i], RectF(pad + i * (chipW + gap), 74.0f, chipW, 28.0f)});
    }

    const float ctrlW = (kTimerW - 2.0f * pad - 2.0f * gap) / 3.0f;
    const TimerAction controls[3] = {kTimerStart, kTimerStop, kTimerReset};
    for (int i = 0; i < 3; ++i) {
        out.push_back(TimerButton{controls[i], RectF(pad + i * (ctrlW + gap), 108.0f, ctrlW, 30.0f)});
    }
    return out;
}

bool TimerActionEnabled(TimerAction action) {
    switch (action) {
        case kTimerStart: return !g_timer.running;
        case kTimerStop: return g_timer.running;
        case kTimerReset: return true;
        default: return true;  // presets and custom can be picked at any time
    }
}

// Returns the selection index for a preset or custom button, or -1 for the control buttons.
int TimerPresetIndex(TimerAction action) {
    if (action == kTimerPreset0) return 0;
    if (action == kTimerPreset1) return 1;
    if (action == kTimerPreset2) return 2;
    if (action == kTimerCustom) return 3;
    return -1;
}

const wchar_t* TimerButtonLabel(TimerAction action) {
    switch (action) {
        case kTimerStart: return L"Start";
        case kTimerStop: return L"Stop";
        case kTimerReset: return L"Reset";
        case kTimerPreset0: return L"5";
        case kTimerPreset1: return L"10";
        case kTimerPreset2: return L"15";
        case kTimerCustom: return L"Custom";
        default: return L"";
    }
}

// True when a point in widget-local coordinates lies on one of the timer's buttons.
bool TimerButtonAt(float x, float y) {
    for (const TimerButton& b : TimerButtons()) {
        if (x >= b.rc.X && x <= b.rc.X + b.rc.Width && y >= b.rc.Y && y <= b.rc.Y + b.rc.Height) {
            return true;
        }
    }
    return false;
}

// Handles a click at a point in widget-local coordinates.
void OnTimerClick(float x, float y) {
    for (const TimerButton& b : TimerButtons()) {
        if (x < b.rc.X || x > b.rc.X + b.rc.Width || y < b.rc.Y || y > b.rc.Y + b.rc.Height) continue;
        if (!TimerActionEnabled(b.action)) return;
        switch (b.action) {
            case kTimerStart: StartTimer(); break;
            case kTimerStop: StopTimer(); break;
            case kTimerReset: ResetTimer(); break;
            default: SelectTimerPreset(TimerPresetIndex(b.action)); break;
        }
        return;
    }
}

void RenderTimerSlot(uint8_t* bits, int surfW, int surfH) {
    UpdateTimer();
    const TimerConfig cfg = SnapshotTimer();
    const TimerState st = g_timer;
    RenderPanelSlot(kTimerSlot, cfg.glass, bits, surfW, surfH, SlotBox(kTimerSlot),
        [&st](Graphics& g, const RectF& rc, Color text, Color soft) {
            FontFamily sans(L"Segoe UI");
            FontFamily light(L"Segoe UI Light");
            const Color accent(255, 255, 159, 10);

            DrawLabel(g, L"TIMER", sans, 10.0f, FontStyleBold,
                      RectF(rc.X + 14.0f, rc.Y + 12.0f, 120.0f, 14.0f),
                      StringAlignmentNear, StringAlignmentCenter, text);
            const wchar_t* status = st.finished ? L"Time's up"
                : st.running ? L"Running"
                : (st.remainingMs < st.durationMs ? L"Paused" : L"Ready");
            const bool paused = !st.finished && !st.running && st.remainingMs < st.durationMs;
            const Color statusColor = st.running ? Color(255, 52, 199, 89)     // green
                : paused ? Color(255, 255, 59, 48)                             // red
                : st.finished ? accent : soft;
            DrawLabel(g, status, sans, 9.0f, FontStyleBold,
                      RectF(rc.X + rc.Width - 136.0f, rc.Y + 12.0f, 120.0f, 14.0f),
                      StringAlignmentFar, StringAlignmentCenter, statusColor);

            // Time remaining, rounded up to the next whole second so the last second still shows.
            const long long secs = std::max<long long>(0, (st.remainingMs + 999) / 1000);
            wchar_t timeText[24];
            if (secs >= 3600) {
                swprintf_s(timeText, L"%lld:%02lld:%02lld", secs / 3600, (secs % 3600) / 60, secs % 60);
            } else {
                swprintf_s(timeText, L"%02lld:%02lld", secs / 60, secs % 60);
            }
            DrawLabel(g, timeText, light, 40.0f, FontStyleRegular,
                      RectF(rc.X, rc.Y + 22.0f, rc.Width, 46.0f),
                      StringAlignmentCenter, StringAlignmentCenter, text);

            // Button positions are widget-local, so add the panel origin before drawing. Clicks
            // use the same widget-local positions, so the drawn buttons match the clickable area.
            for (const TimerButton& b : TimerButtons()) {
                const RectF r(rc.X + b.rc.X, rc.Y + b.rc.Y, b.rc.Width, b.rc.Height);
                const bool enabled = TimerActionEnabled(b.action);
                const int preset = TimerPresetIndex(b.action);
                const bool isChip = preset >= 0;
                const bool active = isChip && preset == st.selected;
                const Color fill = active ? accent
                    : Color(enabled ? 60 : 22, text.GetR(), text.GetG(), text.GetB());
                const Color label = active ? Color(255, 22, 26, 34) : (enabled ? text : soft);
                DrawRoundedRectangle(g, r, r.Height / 2.0f, SolidBrush(fill));
                DrawLabel(g, TimerButtonLabel(b.action), sans, isChip ? 10.0f : 10.5f, FontStyleBold,
                          r, StringAlignmentCenter, StringAlignmentCenter, label);
            }
        });
}

// Plays the system notification sound and shows a balloon. The balloon is shown through a
// temporary tray icon, which is removed again a few seconds later.
void NotifyTimerDone() {
    MessageBeep(MB_ICONASTERISK);
    if (!g_hwnd) return;

    NOTIFYICONDATAW nid = {};
    nid.cbSize = sizeof(nid);
    nid.hWnd = g_hwnd;
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_TIP | NIF_INFO;
    nid.hIcon = LoadIconW(nullptr, IDI_INFORMATION);
    wcscpy_s(nid.szTip, L"LVT Widgets");
    wcscpy_s(nid.szInfoTitle, L"Timer finished");
    wcscpy_s(nid.szInfo, L"Your timer has ended.");
    nid.dwInfoFlags = NIIF_INFO | NIIF_NOSOUND;  // the beep above supplies the sound
    if (!Shell_NotifyIconW(NIM_ADD, &nid)) {
        Shell_NotifyIconW(NIM_MODIFY, &nid);
    }
    SetTimer(g_hwnd, kTimerNotifyRemoveId, 8000, nullptr);
}

void RemoveTimerNotifyIcon() {
    NOTIFYICONDATAW nid = {};
    nid.cbSize = sizeof(nid);
    nid.hWnd = g_hwnd;
    nid.uID = 1;
    Shell_NotifyIconW(NIM_DELETE, &nid);
}

// The wallpaper comes from the monitor under the first enabled widget.
RECT PlacementRect() {
    for (int slot = kWeatherSlot; slot < kSlotCount; ++slot) {
        if (SlotEnabled(slot)) return SlotScreenRect(slot);
    }
    return SlotScreenRect(kWeatherSlot);
}

// Client-area rectangle a slot can paint, including its shadow padding.
RECT SlotPresentRect(int slot) {
    const float s = SlotScale(slot);
    const RectF box = SlotBox(slot);
    const RectF& rc = SlotRc(slot);
    const int pad = static_cast<int>(std::ceil(kShadowPad * s)) + 2;
    const int x = static_cast<int>(std::lround(rc.X * s)) - pad;
    const int y = static_cast<int>(std::lround(rc.Y * s)) - pad;
    const int w = static_cast<int>(std::lround(box.Width * s)) + 2 * pad;
    const int h = static_cast<int>(std::lround(box.Height * s)) + 2 * pad;
    return RECT{x, y, x + w, y + h};
}

RECT ClipRectTo(RECT r, int w, int h) {
    r.left = std::max<LONG>(0, r.left);
    r.top = std::max<LONG>(0, r.top);
    r.right = std::min<LONG>(w, r.right);
    r.bottom = std::min<LONG>(h, r.bottom);
    return r;
}

// Zeroes the surface pixels inside a rectangle that is already clipped to the surface.
void ClearRect(uint8_t* bits, int surfW, const RECT& r) {
    if (r.right <= r.left || r.bottom <= r.top) return;
    const size_t rowBytes = static_cast<size_t>(r.right - r.left) * 4;
    for (LONG y = r.top; y < r.bottom; ++y) {
        std::memset(bits + (static_cast<size_t>(y) * surfW + r.left) * 4, 0, rowBytes);
    }
}

void Render() {
    if (!g_hwnd) return;

    const RECT wa = DesktopWorkArea();
    const int w = wa.right - wa.left;
    const int h = wa.bottom - wa.top;
    if (w <= 0 || h <= 0) return;

    HDC screenDc = GetDC(nullptr);
    if (!screenDc) return;
    if (!EnsureRenderSurface(screenDc, w, h)) {
        ReleaseDC(nullptr, screenDc);
        return;
    }

    // Only the area that widgets cover this frame, or covered last frame, is cleared and presented.
    RECT current = {};
    for (int slot = 0; slot < kSlotCount; ++slot) {
        if (!SlotEnabled(slot)) continue;
        const RECT r = SlotPresentRect(slot);
        UnionRect(&current, &current, &r);
    }
    RECT dirty = {};
    UnionRect(&dirty, &current, &g_prevPresentRect);
    if (g_fullRefresh) {
        dirty = RECT{0, 0, w, h};
        g_fullRefresh = false;
    }
    dirty = ClipRectTo(dirty, w, h);
    g_prevPresentRect = current;
    if (IsRectEmpty(&dirty)) {
        ReleaseDC(nullptr, screenDc);
        return;
    }

    uint8_t* bits = static_cast<uint8_t*>(g_renderSurface.bits);
    ClearRect(bits, w, dirty);

    if (SlotEnabled(kWeatherSlot)) RenderWeatherSlot(bits, w, h);
    if (SlotEnabled(kCalendarSlot)) RenderCalendarSlot(bits, w, h);
    if (SlotEnabled(kClockSlot)) RenderClockSlot(bits, w, h);
    if (SlotEnabled(kRssSlot)) RenderRssSlot(bits, w, h);
    if (SlotEnabled(kCountdownSlot)) RenderCountdownSlot(bits, w, h);
    if (SlotEnabled(kPomodoroSlot)) RenderPomodoroSlot(bits, w, h);
    if (SlotEnabled(kTimerSlot)) RenderTimerSlot(bits, w, h);

    SIZE size = {w, h};
    POINT src = {0, 0};
    POINT pos = {wa.left, wa.top};
    BLENDFUNCTION blend = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
    UPDATELAYEREDWINDOWINFO info = {};
    info.cbSize = sizeof(info);
    info.hdcDst = screenDc;
    info.pptDst = &pos;
    info.psize = &size;
    info.hdcSrc = g_renderSurface.memDc;
    info.pptSrc = &src;
    info.pblend = &blend;
    info.dwFlags = ULW_ALPHA;
    info.prcDirty = &dirty;
    UpdateLayeredWindowIndirect(g_hwnd, &info);
    ReleaseDC(nullptr, screenDc);
}

// ── Window procedure ──

LRESULT CALLBACK WidgetWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            g_hwnd = hwnd;
            MARGINS margins = {-1};
            DwmExtendFrameIntoClientArea(hwnd, &margins);
            UpdateScale();
            for (int slot = 0; slot < kSlotCount; ++slot) {
                if (!LoadSlotPosition(slot)) ApplyDefaultPosition(slot);
                ClampSlotToDesktop(slot);
            }
            UpdateWallpaper(PlacementRect(), true);
            SetTimer(hwnd, kWallpaperTimerId, kWallpaperPollMs, nullptr);
            SetTimer(hwnd, kDayTimerId, kDayTimerMs, nullptr);
            ApplyAnimationTimer(SnapshotWeather());
            ApplyClockTimer(SnapshotClock());
            Render();
            return 0;
        }

        case WM_TIMER:
            if (wParam == kWallpaperTimerId) {
                if (UpdateWallpaper(PlacementRect(), false)) Render();
            } else if (wParam == kAnimTimerId || wParam == kFocusTimerId) {
                Render();
            } else if (wParam == kTimerNotifyRemoveId) {
                KillTimer(hwnd, kTimerNotifyRemoveId);
                RemoveTimerNotifyIcon();
            } else if (wParam == kDayTimerId) {
                SYSTEMTIME now;
                GetLocalTime(&now);
                const int key = now.wYear * 10000 + now.wMonth * 100 + now.wDay;
                if (key != g_lastDayKey) Render();
            }
            return 0;

        case WM_DISPLAYCHANGE:
        case WM_DPICHANGED:
            UpdateScale();
            for (int slot = 0; slot < kSlotCount; ++slot) ClampSlotToDesktop(slot);
            UpdateWallpaper(PlacementRect(), true);
            Render();
            return 0;

        case kWeatherUpdatedMessage:
        case kCalendarUpdatedMessage:
        case kRssUpdatedMessage:
            Render();
            return 0;

        case kSettingsChangedMessage:
            LoadSettings();
            ApplyAnimationTimer(SnapshotWeather());
            ApplyClockTimer(SnapshotClock());
            {
                const WeatherConfig w = SnapshotWeather();
                if (w.useGpu && !g_gpu.ready) InitGpu();
                if (!w.useGpu && g_gpu.ready) ReleaseGpu();
            }
            for (int slot = 0; slot < kSlotCount; ++slot) ClampSlotToDesktop(slot);
            if (g_weatherWake) SetEvent(g_weatherWake);
            if (g_calendarWake) SetEvent(g_calendarWake);
            if (g_rssWake) SetEvent(g_rssWake);
            SyncPomodoroToSettings();
            SyncTimerToSettings();
            Render();
            return 0;

        case WM_NCHITTEST: {
            POINT pt = {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
            return HitTestSlot(pt) >= 0 ? HTCLIENT : HTTRANSPARENT;
        }

        case WM_MOUSEWHEEL: {
            POINT pt = {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
            if (HitTestSlot(pt) == kRssSlot) {
                float ty = 0, th = 0, thumbY = 0, thumbH = 0; int maxScroll = 0;
                if (RssScrollMetrics(ty, th, thumbY, thumbH, maxScroll)) {
                    const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
                    g_rssScroll = std::clamp(g_rssScroll.load() - (delta / WHEEL_DELTA) * 3, 0, maxScroll);
                    Render();
                }
            }
            return 0;
        }

        case WM_LBUTTONDOWN: {
            // The window sits at the work-area origin, so client coordinates plus that origin
            // give the screen coordinates that HitTestSlot expects.
            const RECT wa = DesktopWorkArea();
            POINT pt = {GET_X_LPARAM(lParam) + wa.left, GET_Y_LPARAM(lParam) + wa.top};
            const int slot = HitTestSlot(pt);
            if (slot < 0) return 0;
            if (slot == kTimerSlot) {
                // Buttons act on press. A press on a button never starts a drag, so a
                // slight hand movement during the click cannot cancel it.
                PointF tp = SlotLogicalPoint(slot, lParam);
                tp.X -= SlotRc(kTimerSlot).X;
                tp.Y -= SlotRc(kTimerSlot).Y;
                if (TimerButtonAt(tp.X, tp.Y)) {
                    OnTimerClick(tp.X, tp.Y);
                    Render();
                    return 0;
                }
            }
            if (slot == kPomodoroSlot) {
                // The centre of the ring starts and pauses the timer on press. Pressing anywhere
                // else on the widget still starts a drag.
                PointF pp = SlotLogicalPoint(slot, lParam);
                pp.X -= SlotRc(kPomodoroSlot).X;
                pp.Y -= SlotRc(kPomodoroSlot).Y;
                const float dx = pp.X - kFocusW / 2.0f;
                const float dy = pp.Y - kFocusH / 2.0f;
                if (dx * dx + dy * dy <= kPomodoroCenterR * kPomodoroCenterR) {
                    TogglePomodoro();
                    Render();
                    return 0;
                }
            }
            if (slot == kRssSlot) {
                PointF rp = SlotLogicalPoint(slot, lParam);
                rp.X -= SlotRc(kRssSlot).X; rp.Y -= SlotRc(kRssSlot).Y;
                float ty = 0, th = 0, thumbY = 0, thumbH = 0; int maxScroll = 0;
                if (RssScrollMetrics(ty, th, thumbY, thumbH, maxScroll) && rp.X >= kRssW - 17.0f && rp.Y >= ty) {
                    if (rp.Y >= thumbY && rp.Y <= thumbY + thumbH) {
                        g_rssThumbDragging = true; g_rssThumbDragOffset = rp.Y - thumbY;
                    } else {
                        const RectF rb = SlotBox(kRssSlot);
                        const int visible = std::max(1, static_cast<int>((rb.Height - kRssHeaderH - 12.0f) / kRssRowH));
                        g_rssScroll = std::clamp(g_rssScroll.load() + (rp.Y < thumbY ? -visible : visible), 0, maxScroll);
                        Render(); return 0;
                    }
                    SetCapture(hwnd); return 0;
                }
            }
            const PointF logical = SlotLogicalPoint(slot, lParam);
            const RectF& rc = SlotRc(slot);
            g_dragging = true;
            g_dragMoved = false;
            g_dragSlot = slot;
            g_dragDelta = PointF(logical.X - rc.X, logical.Y - rc.Y);
            g_dragStart = logical;
            SetCapture(hwnd);
            return 0;
        }

        case WM_MOUSEMOVE: {
            if (g_rssThumbDragging) {
                PointF rp = SlotLogicalPoint(kRssSlot, lParam);
                rp.X -= SlotRc(kRssSlot).X; rp.Y -= SlotRc(kRssSlot).Y;
                float ty = 0, th = 0, thumbY = 0, thumbH = 0; int maxScroll = 0;
                if (RssScrollMetrics(ty, th, thumbY, thumbH, maxScroll)) {
                    const float travel = std::max(1.0f, th - thumbH);
                    const float pos = Clamp(rp.Y - g_rssThumbDragOffset - ty, 0.0f, travel);
                    g_rssScroll = static_cast<int>(std::lround(pos / travel * maxScroll));
                    Render();
                }
                return 0;
            }
            if (!g_dragging || g_dragSlot < 0) return 0;
            if (!(wParam & MK_LBUTTON)) {
                g_dragging = false;
                ReleaseCapture();
                return 0;
            }
            const PointF pt = SlotLogicalPoint(g_dragSlot, lParam);
            if (std::fabs(pt.X - g_dragStart.X) > 3.0f || std::fabs(pt.Y - g_dragStart.Y) > 3.0f) {
                g_dragMoved = true;
            }
            const RECT wa = DesktopWorkArea();
            const float s = SlotScale(g_dragSlot);
            const RectF box = SlotBox(g_dragSlot);
            const float maxX = std::max(0.0f, (wa.right - wa.left) / s - box.Width);
            const float maxY = std::max(0.0f, (wa.bottom - wa.top) / s - box.Height);
            RectF& rc = SlotRc(g_dragSlot);
            rc.X = Clamp(pt.X - g_dragDelta.X, 0.0f, maxX);
            rc.Y = Clamp(pt.Y - g_dragDelta.Y, 0.0f, maxY);
            SnapSlotToEdges(g_dragSlot);
            Render();
            return 0;
        }

        case WM_LBUTTONUP: {
            if (g_rssThumbDragging) { g_rssThumbDragging = false; ReleaseCapture(); return 0; }
            const bool moved = g_dragMoved;
            const bool wasDragging = g_dragging;
            const int slot = g_dragSlot;
            g_dragging = false;
            g_dragMoved = false;
            g_dragSlot = -1;
            ReleaseCapture();
            if (wasDragging && slot >= 0 && moved) {
                SnapSlotToEdges(slot);
                UpdateWallpaper(PlacementRect(), false);
                SaveSlotPosition(slot);
                Render();
            } else if (wasDragging && slot == kWeatherSlot) {
                const WeatherConfig wc = SnapshotWeather();
                wchar_t link[512];
                swprintf_s(link, L"https://open-meteo.com/en/docs#latitude=%.4f&longitude=%.4f",
                           wc.latitude, wc.longitude);
                ShellExecuteW(nullptr, L"open", link, nullptr, nullptr, SW_SHOWNORMAL);
                if (g_weatherWake) SetEvent(g_weatherWake);
            } else if (wasDragging && slot == kCalendarSlot && g_calendarWake) {
                SetEvent(g_calendarWake);
            } else if (wasDragging && slot == kClockSlot) {
                Render();
            } else if (wasDragging && slot == kRssSlot) {
                PointF rp = SlotLogicalPoint(slot, lParam);
                rp.X -= SlotRc(kRssSlot).X; rp.Y -= SlotRc(kRssSlot).Y;
                const int row = static_cast<int>((rp.Y - kRssHeaderH) / kRssRowH);
                std::shared_ptr<const std::vector<RssItem>> items;
                { std::lock_guard<std::mutex> lock(g_mutex); items = g_rssItems; }
                const int index = g_rssScroll.load() + row;
                if (row >= 0 && items && index >= 0 && index < static_cast<int>(items->size())) {
                    const std::wstring& link = (*items)[static_cast<size_t>(index)].link;
                    if (link.rfind(L"https://", 0) == 0 || link.rfind(L"http://", 0) == 0)
                        ShellExecuteW(nullptr, L"open", link.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
                } else if (g_rssWake) {
                    SetEvent(g_rssWake);
                }
            }
            return 0;
        }

        case WM_CAPTURECHANGED:
            g_rssThumbDragging = false;
            if (g_dragging && g_dragMoved && g_dragSlot >= 0) SaveSlotPosition(g_dragSlot);
            g_dragging = false;
            g_dragMoved = false;
            g_dragSlot = -1;
            return 0;

        case kTimerDoneMessage:
            NotifyTimerDone();
            return 0;

        case WM_RBUTTONUP: {
            const RECT wa = DesktopWorkArea();
            POINT pt = {GET_X_LPARAM(lParam) + wa.left, GET_Y_LPARAM(lParam) + wa.top};
            if (HitTestSlot(pt) == kPomodoroSlot) {
                ResetPomodoro();
                Render();
            }
            return 0;
        }

        case WM_DESTROY:
            KillTimer(hwnd, kWallpaperTimerId);
            KillTimer(hwnd, kAnimTimerId);
            KillTimer(hwnd, kDayTimerId);
            KillTimer(hwnd, kClockTimerId);
            KillTimer(hwnd, kFocusTimerId);
            KillTimer(hwnd, kTimerNotifyRemoveId);
            RemoveTimerNotifyIcon();
            SaveSlotPosition(kWeatherSlot);
            SaveSlotPosition(kCalendarSlot);
            SaveSlotPosition(kClockSlot);
            SaveSlotPosition(kRssSlot);
            SaveSlotPosition(kCountdownSlot);
            SaveSlotPosition(kPomodoroSlot);
            SaveSlotPosition(kTimerSlot);
            DestroyRenderSurface();
            g_hwnd = nullptr;
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

DWORD WINAPI UiThreadProc(LPVOID) {
    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

    GdiplusStartupInput gdiplusInput;
    GdiplusStartup(&g_gdiplusToken, &gdiplusInput, nullptr);

    if (SnapshotWeather().useGpu) InitGpu();

    HINSTANCE instance = GetModuleHandleW(nullptr);

    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(wc);
    wc.hInstance = instance;
    wc.lpfnWndProc = WidgetWndProc;
    wc.lpszClassName = kClassName;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    RegisterClassExW(&wc);

    const RECT wa = DesktopWorkArea();
    g_hwnd = CreateWindowExW(
        WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE,
        kClassName, L"LVT Widgets", WS_POPUP,
        wa.left, wa.top, wa.right - wa.left, wa.bottom - wa.top,
        nullptr, nullptr, instance, nullptr);

    if (g_hwnd) {
        SetWindowPos(g_hwnd, HWND_BOTTOM, 0, 0, 0, 0,
                     SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOSIZE);
        ShowWindow(g_hwnd, SW_SHOWNOACTIVATE);
    }

    MSG msg;
    while (!g_stopping && GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    if (g_hwnd) DestroyWindow(g_hwnd);
    UnregisterClassW(kClassName, instance);
    ReleaseGpu();
    SafeRelease(g_desktopWallpaper);
    delete g_wpImage;
    g_wpImage = nullptr;
    GdiplusShutdown(g_gdiplusToken);
    CoUninitialize();
    return 0;
}

}  // namespace

// ── Dedicated tool-process lifecycle ────────────────────────────────────────
// Widget windows, rendering, network workers, and COM/GDI+/D3D resources are
// created only in the child process started with: -tool-mod "lvt-widgets".
// The Windhawk launcher instance must never initialize widget implementation.
bool g_isDedicatedToolProcess = false;

BOOL WhTool_ModInit() {
    if (!g_isDedicatedToolProcess) {
        Wh_Log(L"Refusing widget initialization outside the dedicated tool process");
        return FALSE;
    }
    g_stopping = false;
    g_weatherWake = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    g_calendarWake = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    g_rssWake = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (!g_weatherWake || !g_calendarWake || !g_rssWake) return FALSE;

    LoadSettings();

    g_uiThread = CreateThread(nullptr, 0, UiThreadProc, nullptr, 0, &g_uiThreadId);
    if (!g_uiThread) return FALSE;

    g_weatherThread = CreateThread(nullptr, 0, WeatherThreadProc, nullptr, 0, nullptr);
    g_calendarThread = CreateThread(nullptr, 0, CalendarThreadProc, nullptr, 0, nullptr);
    g_rssThread = CreateThread(nullptr, 0, RssThreadProc, nullptr, 0, nullptr);
    return g_weatherThread != nullptr && g_calendarThread != nullptr && g_rssThread != nullptr;
}

void WhTool_ModSettingsChanged() {
    if (!g_isDedicatedToolProcess) return;
    if (g_hwnd) {
        PostMessageW(g_hwnd, kSettingsChangedMessage, 0, 0);
    } else {
        LoadSettings();
    }
}

void WhTool_ModUninit() {
    if (!g_isDedicatedToolProcess) return;
    g_stopping = true;
    if (g_weatherWake) SetEvent(g_weatherWake);
    if (g_calendarWake) SetEvent(g_calendarWake);
    if (g_rssWake) SetEvent(g_rssWake);

    for (HANDLE* thread : {&g_weatherThread, &g_calendarThread, &g_rssThread}) {
        if (*thread) {
            WaitForSingleObject(*thread, 15000);
            CloseHandle(*thread);
            *thread = nullptr;
        }
    }

    if (g_uiThreadId) PostThreadMessageW(g_uiThreadId, WM_QUIT, 0, 0);
    if (g_uiThread) {
        WaitForSingleObject(g_uiThread, 3000);
        CloseHandle(g_uiThread);
        g_uiThread = nullptr;
    }

    if (g_weatherWake) {
        CloseHandle(g_weatherWake);
        g_weatherWake = nullptr;
    }
    if (g_calendarWake) { CloseHandle(g_calendarWake); g_calendarWake = nullptr; }
    if (g_rssWake) { CloseHandle(g_rssWake); g_rssWake = nullptr; }
}

// ── Windhawk dedicated-process bootstrap ────────────────────────────────────
// @include windhawk.exe is intentional. Windhawk loads this mod in its own
// process; Wh_ModAfterInit starts a second windhawk.exe instance with the
// -tool-mod switch. Only that child executes WhTool_Mod* and owns the widgets.
// No Explorer injection target or Explorer-resident widget code is used.
bool g_isToolModProcessLauncher;
HANDLE g_toolModProcessMutex;

void WINAPI EntryPoint_Hook() {
    Wh_Log(L">");
    ExitThread(0);
}

BOOL Wh_ModInit() {
    DWORD sessionId;
    if (ProcessIdToSessionId(GetCurrentProcessId(), &sessionId) && sessionId == 0)
        return FALSE;

    bool isExcluded = false, isToolModProcess = false, isCurrentToolModProcess = false;
    int argc;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLine(), &argc);
    if (!argv) {
        Wh_Log(L"CommandLineToArgvW failed");
        return FALSE;
    }

    for (int i = 1; i < argc; i++) {
        if (wcscmp(argv[i], L"-service") == 0 ||
            wcscmp(argv[i], L"-service-start") == 0 ||
            wcscmp(argv[i], L"-service-stop") == 0) {
            isExcluded = true;
            break;
        }
    }
    for (int i = 1; i < argc - 1; i++) {
        if (wcscmp(argv[i], L"-tool-mod") == 0) {
            isToolModProcess = true;
            if (wcscmp(argv[i + 1], WH_MOD_ID) == 0) isCurrentToolModProcess = true;
            break;
        }
    }
    LocalFree(argv);

    if (isExcluded) return FALSE;

    if (isCurrentToolModProcess) {
        g_toolModProcessMutex = CreateMutex(nullptr, TRUE, L"windhawk-tool-mod_" WH_MOD_ID);
        if (!g_toolModProcessMutex) {
            Wh_Log(L"CreateMutex failed");
            ExitProcess(1);
        }
        if (GetLastError() == ERROR_ALREADY_EXISTS) {
            Wh_Log(L"Tool mod already running (%s)", WH_MOD_ID);
            ExitProcess(1);
        }

        // This is the only path that grants permission to initialize widgets.
        g_isDedicatedToolProcess = true;
        if (!WhTool_ModInit()) ExitProcess(1);

        IMAGE_DOS_HEADER* dosHeader = (IMAGE_DOS_HEADER*)GetModuleHandle(nullptr);
        IMAGE_NT_HEADERS* ntHeaders = (IMAGE_NT_HEADERS*)((BYTE*)dosHeader + dosHeader->e_lfanew);
        void* entryPoint = (BYTE*)dosHeader + ntHeaders->OptionalHeader.AddressOfEntryPoint;
        Wh_SetFunctionHook(entryPoint, (void*)EntryPoint_Hook, nullptr);
        return TRUE;
    }

    if (isToolModProcess) return FALSE;

    g_isToolModProcessLauncher = true;
    return TRUE;
}

void Wh_ModAfterInit() {
    if (!g_isToolModProcessLauncher) return;

    WCHAR currentProcessPath[MAX_PATH];
    switch (GetModuleFileName(nullptr, currentProcessPath, ARRAYSIZE(currentProcessPath))) {
        case 0:
        case ARRAYSIZE(currentProcessPath):
            Wh_Log(L"GetModuleFileName failed");
            return;
    }

    WCHAR commandLine[MAX_PATH + 2 +
                      (sizeof(L" -tool-mod \"" WH_MOD_ID "\"") / sizeof(WCHAR)) - 1];
    swprintf_s(commandLine, L"\"%s\" -tool-mod \"%s\"", currentProcessPath, WH_MOD_ID);

    HMODULE kernelModule = GetModuleHandle(L"kernelbase.dll");
    if (!kernelModule) {
        kernelModule = GetModuleHandle(L"kernel32.dll");
        if (!kernelModule) {
            Wh_Log(L"No kernelbase.dll/kernel32.dll");
            return;
        }
    }

    using CreateProcessInternalW_t = BOOL(WINAPI*)(
        HANDLE, LPCWSTR, LPWSTR, LPSECURITY_ATTRIBUTES, LPSECURITY_ATTRIBUTES,
        WINBOOL, DWORD, LPVOID, LPCWSTR, LPSTARTUPINFOW, LPPROCESS_INFORMATION, PHANDLE);
    CreateProcessInternalW_t pCreateProcessInternalW =
        (CreateProcessInternalW_t)GetProcAddress(kernelModule, "CreateProcessInternalW");
    if (!pCreateProcessInternalW) {
        Wh_Log(L"No CreateProcessInternalW");
        return;
    }

    STARTUPINFO si{.cb = sizeof(STARTUPINFO), .dwFlags = STARTF_FORCEOFFFEEDBACK};
    PROCESS_INFORMATION pi;
    if (!pCreateProcessInternalW(nullptr, currentProcessPath, commandLine,
                                 nullptr, nullptr, FALSE, NORMAL_PRIORITY_CLASS,
                                 nullptr, nullptr, &si, &pi, nullptr)) {
        Wh_Log(L"CreateProcess failed");
        return;
    }
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

void Wh_ModSettingsChanged() {
    if (g_isToolModProcessLauncher) return;
    WhTool_ModSettingsChanged();
}

void Wh_ModUninit() {
    if (g_isToolModProcessLauncher) return;
    WhTool_ModUninit();
    ExitProcess(0);
}

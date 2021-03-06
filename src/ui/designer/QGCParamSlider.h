#ifndef QGCPARAMSLIDER_H
#define QGCPARAMSLIDER_H

#include <QWidget>
#include <QAction>

#include "QGCToolWidgetItem.h"

namespace Ui
{
class QGCParamSlider;
}

class QGCParamSlider : public QGCToolWidgetItem
{
    Q_OBJECT

public:
    explicit QGCParamSlider(QWidget *parent = 0);
    ~QGCParamSlider();

public slots:
    void startEditMode();
    void endEditMode();
    /** @brief Send the parameter to the MAV */
    void sendParameter();
    /** @brief Set the slider value as parameter value */
    void setSliderValue(int sliderValue);
    /** @brief Update the UI with the new parameter value */
    void setParameterValue(int uas, int component, int paramCount, int paramIndex, QString parameterName, const QVariant value);
    void writeSettings(QSettings& settings);
    void readSettings(const QSettings& settings);
    void readSettings(const QString& pre,const QVariantMap& settings);
    void refreshParamList();
    void setActiveUAS(UASInterface *uas);
    void selectComponent(int componentIndex);
    void selectParameter(int paramIndex);
    /** @brief Set a double parameter value */
    void setParamValue(double value);
    /** @brief Set an integer parameter value */
    void setParamValue(int value);
    /** @brief Show descriptive text next to slider */
    void showInfo(bool enable);
    /** @brief Show tool tip of calling element */
    void showTooltip();

protected slots:
    /** @brief Request the parameter of this widget from the MAV */
    void requestParameter();

protected:
    bool visibleEnabled;
    QString visibleParam;
    int visibleVal;
    //The below variables, and usage in QGCParamSlider.cc are a bit of a hack, since disconnect() does not seem to take effect
    //immediatly (perhaps it is put into the event loop?) - MLC
    bool valueModLock;              ///< Used to keep the slider/spinboxes from updating each other during user input
    bool valueModLockParam;         ///< Used to keep the slider/spinboxes from udpating each other when a new parametervalue comes in
    QString parameterName;         ///< Key/Name of the parameter
    QVariant parameterValue;          ///< Value of the parameter
    double parameterScalingFactor; ///< Factor to scale the parameter between slider and true value
    float parameterMin;
    float parameterMax;
    int component;                 ///< ID of the MAV component to address
    double scaledInt;
    void changeEvent(QEvent *e);

    /** @brief Convert scaled int to float */

    float scaledIntToFloat(int sliderValue);
    int floatToScaledInt(float value);

private:
    Ui::QGCParamSlider *ui;
};

#endif // QGCPARAMSLIDER_H

#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H

#include <QPushButton>
#include <QPainter>
#include <QSvgRenderer>

/**
 * @class GameButton
 * @brief A custom game button widget with visual state management
 */
class GameButton : public QPushButton
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a GameButton
     * @param id The unique identifier of the button
     * @param parent The parent widget (default is nullptr)
     */
    explicit GameButton(int id, QWidget *parent = nullptr);
    /**
     * @brief Sets the visual state of the button
     * @param state The new state of the button ('x', 'o', or ' ')
     */
    void setState(char state);
    /**
     * @brief Gets the unique identifier of the button
     * @return The button's identifier
     */
    int id();

protected:
    /**
     * @brief Overrides the paintEvent to draw the button's visual state
     * @param event The paint event
     */
    void paintEvent(QPaintEvent *event) override;
    /**
     * @brief Overrides the mouseReleaseEvent to emit the 'hit' signal
     * @param event The mouse release event
     */
    void mouseReleaseEvent(QMouseEvent  *event) override;

signals:
    /**
     * @brief Emitted when the button is released
     * @param id The identifier of the button
     */
    void hit(int id);

private:
    int m_id;
    char m_state;

    QSvgRenderer m_svgRenderer;
    bool m_renderState;
};

#endif // GAMEBUTTON_H
